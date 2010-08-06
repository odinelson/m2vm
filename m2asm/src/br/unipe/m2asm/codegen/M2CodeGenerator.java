package br.unipe.m2asm.codegen;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;

import br.unipe.m2asm.machine.M2ExeHeader;
import br.unipe.m2asm.machine.Machine;
import br.unipe.m2asm.machine.Opcode;
import br.unipe.m2asm.machine.Reg;
import br.unipe.m2asm.parse.ASTChar;
import br.unipe.m2asm.parse.ASTDeclarator;
import br.unipe.m2asm.parse.ASTDeclaratorNonInit;
import br.unipe.m2asm.parse.ASTId;
import br.unipe.m2asm.parse.ASTInteger;
import br.unipe.m2asm.parse.ASTLabel;
import br.unipe.m2asm.parse.ASTMemOffset;
import br.unipe.m2asm.parse.ASTMemRef;
import br.unipe.m2asm.parse.ASTMemSize;
import br.unipe.m2asm.parse.ASTOpcode;
import br.unipe.m2asm.parse.ASTProg;
import br.unipe.m2asm.parse.ASTPseudoStmt;
import br.unipe.m2asm.parse.ASTRegFloat;
import br.unipe.m2asm.parse.ASTRegInt;
import br.unipe.m2asm.parse.ASTStackDecl;
import br.unipe.m2asm.parse.ASTStmt;
import br.unipe.m2asm.parse.ASTStr;
import br.unipe.m2asm.parse.ASTValues;
import br.unipe.m2asm.parse.M2AsmNode;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;
import br.unipe.m2asm.util.Util;

/**
 * @author Odilon
 *
 */
public class M2CodeGenerator extends M2AsmParserVisitorAdapter {

	private List<ByteBuffer> codeBytes = new ArrayList<ByteBuffer>();
	private List<ByteBuffer> dataBytes = new ArrayList<ByteBuffer>();
	
	private ByteBuffer codeBuffer;
	private ByteBuffer dataBuffer;
	
	///private Section currSection;
	// Code and Data size are given in constructor and pre-calculated by 1st pass, in LabelResolver class
	private int codeSize;
	private int dataSize;
	// Stack size, in BYTES. This isn't final because a %STACK directive may override it.
	private int stackSize = 512;
	// Non initialized data size, in BYTES.
	private int nonInitDataSize = 0;
	
	public M2CodeGenerator(int codeSize, int dataSize) {
		this.codeSize = codeSize;
		this.dataSize = dataSize;
		codeBuffer = ByteBuffer.allocate(codeSize);
		codeBuffer.order(ByteOrder.LITTLE_ENDIAN);
		dataBuffer = ByteBuffer.allocate(dataSize);
		dataBuffer.order(ByteOrder.LITTLE_ENDIAN);
	}
	
	private void emit(byte b) {
		codeBuffer.put(b);
	}
	
	private void emit(byte[] b) {
		codeBuffer.put(b);
	}
	
	private void emitData(byte b) {
		dataBuffer.put(b);
	}
	
	private void emitData(short s) {
		dataBuffer.putShort(s);
	}
	
	private void emitData(String s) {
		dataBuffer.put(s.getBytes());
	}
	
	private void emitData(byte[] b) {
		dataBuffer.put(b);
	}
	
	@Override
	public void visit(ASTProg node, SymbolTable data) {
		//System.out.println("Iniciando geração de código...");
		super.visit(node, data);
		//System.out.println("Finalizado.");
		System.out.println("Symbol Table = " + data);
	}

//	@Override
//	public void visit(ASTSegment node, SymbolTable data) {
//		System.out.println("Entrando em segmento: " + node.value);
//		currSection = Section.valueOf(node.value);
//		super.visit(node, data);
//	}

//	@Override
//	public void visit(ASTLabel node, SymbolTable data) {
//		super.visit(node, data);
//		int address = currSection == Section.CODE ? getCodeSize() : getDataSize(); 
//		data.addLabel(node.value, address, currSection);
//	}

	@Override
	public void visit(ASTStmt node, SymbolTable data) {
		super.visit(node, data);
		ByteBuffer buff = ByteBuffer.allocate(4);
		buff.order(ByteOrder.LITTLE_ENDIAN);
		
		M2AsmNode firstNode = (M2AsmNode) node.jjtGetChild(0);
		int numArgs = node.jjtGetNumChildren();
		Opcode op = null;
		
		if (firstNode instanceof ASTLabel) {
			numArgs -= 2;
			ASTOpcode opNode = (ASTOpcode) node.jjtGetChild(1);
			op = Opcode.valueOf(opNode.value);
		}
		else {
			numArgs--;
			ASTOpcode opNode = (ASTOpcode) node.jjtGetChild(0);
			op = Opcode.valueOf(opNode.value);
		}
		buff.put(op.getCode());
				
		if (numArgs >= 1) {  //we have arguments!
			buildArgument(node, data, buff, 1);
			if (numArgs == 2) {  //we have a 2nd argument!
				buildArgument(node, data, buff, 2);
			}
		}
		///codeBytes.add(buff);
		emit(buff.array());
		//debug
		System.out.println("Encoded CODE bytes: " + Util.toHexString(buff.array()));
	}

	private void buildArgument(ASTStmt node, SymbolTable data, ByteBuffer buff, int argNum) {
		M2AsmNode argNode = (M2AsmNode) node.jjtGetChild(argNum);
		if (argNode instanceof ASTInteger || argNode instanceof ASTChar) {
			buildImmediate(argNode.value, buff);
//			String val = argNode.value;
//			Integer x = null;
//			if (argNode instanceof ASTChar) {
//				x = (int) val.charAt(1); //o 1o char é o delimitador '
//			}
//			else x = Integer.parseInt(val);
//			buff.position(2);
//			buff.putShort(x.shortValue());
//			patchOpcodeForImmediate(buff);
		}
		else if (argNode instanceof ASTRegInt || argNode instanceof ASTRegFloat) {
			buildRegValue(argNode, buff, argNum);
		}
		else if (argNode instanceof ASTId) {  //label reference to the ADDRESS
			String id = argNode.value;
			if (data.isLabel(id)) {
				int addr = data.resolveLabel(id);
				// adresses of labels are ABSOLUTE
				if (data.getDeclaredSection(id) == Section.DATA) {
					addr += codeSize;  //DATA is after CODE
				}
				// if we're in a jump-kind instruction, must patch the address to be RELATIVE
				addr = patchAddressForJump(buff, addr);
				// put offset  (TODO : test this with JUMP instructions)
				buff.position(2);
				buff.putShort((short) addr);
				patchOpcodeForImmediate(buff);
			}
//			else if (data.isDef(id)) {
//				buildImmediate(data.resolveDef(id), buff);
//			}
		}
		else if (argNode instanceof ASTMemRef) {
			//an ASTMemRef node has the following structure:
			//  ASTMemRef
			//    ASTRegInt    (compulsory)
			//    ASTMemOffset (optional, default 0)
			//    ASTMemSize   (optional, default WORD)
			//or
			//  ASTMemRef
			//    ASTId    (compulsory)
			//    ASTMemSize   (optional, default WORD)
			//the 2nd form is just a shorthand for the first, where RegInt is DT (or UD)
			//and MemOffset is obtained from symTab
			if (argNode.jjtGetChild(0) instanceof ASTId) {  //label reference to the CONTENT
				String id = ((ASTId) argNode.jjtGetChild(0)).value;
				int addr = data.resolveLabel(id);
				// DT is assumed (TODO: support UD)
				buildRegValue(Reg.DT, buff, argNum);
				// put offset from DT
				buff.position(2);
				buff.putShort((short) addr);
			}
			else {
				buildRegValue((M2AsmNode) argNode.jjtGetChild(0), buff, argNum);
				int numChildren = argNode.jjtGetNumChildren();
				if (numChildren > 1) {
					if (argNode.jjtGetChild(1) instanceof ASTMemOffset) {
						short offset = Short.parseShort(((ASTMemOffset) argNode.jjtGetChild(1)).value);
						buff.putShort(offset);
					}
					else { //when ASTMemOffset is not present, 2nd child is ASTMemSize  (ex: LOD R0, *DT:BYTE)
						patchOpcodeToMemRefSize((ASTMemSize) argNode.jjtGetChild(1), buff);
					}
					if (numChildren == 3) {
						patchOpcodeToMemRefSize((ASTMemSize) argNode.jjtGetChild(2), buff);
					}
				}
			}
		}
		// and so on, for the other types of arguments (are there any more??)		
	}
	
	private void buildImmediate(String val, ByteBuffer buff) {
		Integer x = null;
		if (val.charAt(0) == '\'') { //o 1o char é o delimitador ', entao é um char
			x = (int) val.charAt(1); 
		}
		else x = Integer.parseInt(val);
		buff.position(2);
		buff.putShort(x.shortValue());
		patchOpcodeForImmediate(buff);
	}
	
	private void patchOpcodeForImmediate(ByteBuffer buff) {
		byte op = buff.get(0);
		buff.position(0);
		if (op == Opcode.LOD.getCode()) {
			buff.put(Opcode.LODI.getCode());
		}
		else if (op == Opcode.ADD.getCode()) {
			buff.put(Opcode.ADDI.getCode());
		}
		else if (op == Opcode.CMP.getCode()) {
			buff.put(Opcode.CMPI.getCode());
		}
		// TODO implement for other opcodes...
	}
	
	private int patchAddressForJump(ByteBuffer buff, int address) {
		byte op = buff.get(0);
		buff.position(0);
		if (op == Opcode.JMP.getCode() ||
			op == Opcode.JE.getCode() ||
			op == Opcode.JNE.getCode() ||
			op == Opcode.JL.getCode() ||
			op == Opcode.JLE.getCode() ||
			op == Opcode.JG.getCode() ||
			op == Opcode.JGE.getCode() ||
			op == Opcode.CALL.getCode()
		) {
			//address is relative to next instruction
			///int currAddress = (codeBytes.size() + 1) * Machine.WORD_SIZE;
			int currAddress = codeBuffer.position() + Machine.WORD_SIZE;
			System.out.println("currAddress = " + currAddress + "; target = " + address);
			return address - currAddress;
		}
		// if we're not in a jump instruction, this method is a no-op
		else return address;
	}
	
	private void buildRegValue(M2AsmNode argNode, ByteBuffer buff, int argNum) {
		buildRegValue(Reg.valueOf(argNode.value), buff, argNum);
	}
	
	private void buildRegValue(Reg r, ByteBuffer buff, int argNum) {
		buff.position(1);
		byte b = buff.get();
		buff.position(1);  //get() incrementa a posição...
		if (argNum == 1)
			b = (byte) ((r.getValue() << 4) | 0);
		else
			b = (byte) (b | r.getValue());
		buff.put(b);
	}
	
	private void patchOpcodeToMemRefSize(ASTMemSize sizeNode, ByteBuffer buff) {
		if (sizeNode.value.equals("BYTE")) {
			byte op = buff.get(0);
			buff.position(0);
			if (op == Opcode.LOD.getCode())
				buff.put(Opcode.LODB.getCode());
			else if (op == Opcode.STOR.getCode())
				buff.put(Opcode.STORB.getCode());
		}
	}

	@Override
	public void visit(ASTPseudoStmt node, SymbolTable data) {
		super.visit(node, data);
		M2AsmNode firstChild = (M2AsmNode) node.jjtGetChild(0);
		ByteBuffer buff = null;
		if (firstChild instanceof ASTDeclarator) {
			int size = firstChild.value.equals("DB") ? 1 : Machine.WORD_SIZE;
			ASTValues valuesNode = (ASTValues) node.jjtGetChild(1);
			int numValues = valuesNode.jjtGetNumChildren();
			for (int i = 0; i < numValues; i++) {
				M2AsmNode valNode = (M2AsmNode) valuesNode.jjtGetChild(i);
				if (valNode instanceof ASTInteger) {
					// TODO FIXME no need to use these temporary buffers... could just emitData(...)
					buff = ByteBuffer.allocate(size);
					buff.order(ByteOrder.LITTLE_ENDIAN);
					if (size == 1)
						buff.put(Byte.parseByte(valNode.value));
					else buff.putInt(Integer.parseInt(valNode.value));///buff.putShort(Short.parseShort(valNode.value));
					///dataBytes.add(buff);
					emitData(buff.array());
					System.out.println("Encoded DATA bytes: " + Util.toHexString(buff.array()));
				}
				else if (valNode instanceof ASTChar) {
					int x = (int) valNode.value.charAt(1); //o 1o char é o delimitador '
					buff = ByteBuffer.allocate(1);
					buff.order(ByteOrder.LITTLE_ENDIAN);
					buff.put((byte) x);
					///dataBytes.add(buff);
					emitData(buff.array());	
					System.out.println("Encoded DATA bytes: " + Util.toHexString(buff.array()));
				}
				else if (valNode instanceof ASTStr) {
					buff = ByteBuffer.allocate(valNode.value.length());
					buff.order(ByteOrder.LITTLE_ENDIAN);
					buff.put(valNode.value.getBytes());
					///dataBytes.add(buff);
					emitData(buff.array());
					System.out.println("Encoded DATA bytes: " + Util.toHexString(buff.array()));
				}
			}
		}
		else if (firstChild instanceof ASTDeclaratorNonInit) {
			// FIXME  Code partially repeated from visit(ASTStackDecl)
			int size = firstChild.value.equals("RESB") ? 1 : Machine.WORD_SIZE;
			int val = Integer.parseInt(((ASTInteger) node.jjtGetChild(1)).value);
			size *= val;
			nonInitDataSize = size;
		}
	}
	
	@Override
	public void visit(ASTStackDecl node, SymbolTable data) {
		super.visit(node, data);
		ASTDeclaratorNonInit nodeDecl = (ASTDeclaratorNonInit) node.jjtGetChild(0);
		int size = nodeDecl.value.equals("RESB") ? 1 : Machine.WORD_SIZE;
		int val = Integer.parseInt(((ASTInteger) node.jjtGetChild(1)).value);
		size *= val;
		if (size != stackSize) {
			System.out.println("** Setting stackSize to " + size + " bytes.");
			stackSize = size;
		}
	}

//	public int getCodeSize() {
//		return codeBytes.size() * Machine.WORD_SIZE;
//	}
//	
//	public int getDataSize() {
//		int count = 0;
//		for (ByteBuffer buff : dataBytes) {
//			count += buff.capacity();
//		}
//		return count;
//	}
	
	public byte[] getCodeBytes() {
//		ByteBuffer codeBuff = ByteBuffer.allocate(codeSize);
//		codeBuff.order(ByteOrder.LITTLE_ENDIAN);
//		short currAddr = 0;
//		for (ByteBuffer buff : codeBytes) {
//			///System.out.println("Encoded bytes: " + Util.toHexString(buff.array()));
//			codeBuff.put(buff.array());
//			//advance
//			currAddr += 4;
//		}
//		return codeBuff.array();
		return codeBuffer.array();
	}
	
	public byte[] getDataBytes() {
//		ByteBuffer dataBuff = ByteBuffer.allocate(dataSize);
//		dataBuff.order(ByteOrder.LITTLE_ENDIAN);
//		for (ByteBuffer buff : dataBytes) {
//			dataBuff.put(buff.array());
//		}
//		return dataBuff.array();
		return dataBuffer.array();
	}
	
	public void createFile(String fileName) {
		M2ExeHeader hdr = new M2ExeHeader();
		byte[] codeBytes = getCodeBytes();
		byte[] dataBytes = getDataBytes();
		hdr.codeSize = codeSize;
		hdr.dataSize = dataSize;
		hdr.nonInitDataSize = nonInitDataSize;
		hdr.stackSize = stackSize;
		try {
			FileOutputStream out = new FileOutputStream(fileName);
			out.write(hdr.getBytes());
			out.write(codeBytes);
			out.write(dataBytes);
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.printf("File \"%s\" successfully assembled.\n", fileName);
	}
}
