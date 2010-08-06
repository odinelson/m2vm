package br.unipe.m2asm.semant;

import br.unipe.m2asm.codegen.SymbolTable;
import br.unipe.m2asm.machine.Opcode;
import br.unipe.m2asm.parse.ASTChar;
import br.unipe.m2asm.parse.ASTInteger;
import br.unipe.m2asm.parse.ASTLabel;
import br.unipe.m2asm.parse.ASTOpcode;
import br.unipe.m2asm.parse.ASTRegFloat;
import br.unipe.m2asm.parse.ASTRegInt;
import br.unipe.m2asm.parse.ASTStmt;
import br.unipe.m2asm.parse.M2AsmNode;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;

/**
 * Checks the validity of the operands for certain opcodes.
 * For example:  LOD Reg, Reg   (should be CPY Reg, Reg)
 * 
 * @author Odilon
 *
 */
public class OperandChecker extends M2AsmParserVisitorAdapter {

	private void errorInvalidOp(Opcode op, String arg1, String arg2) {
		// FIXME : use the same semantic error handling as in SLAPplus...
		throw new RuntimeException("Invalid operation for operands: " + op + " " + arg1 + "," + arg2);
	}
	
	@Override
	public void visit(ASTStmt node, SymbolTable data) {
		super.visit(node, data);
		// FIXME {code copied from M2CodeGenerator.visit(ASTStmt) - refactor}
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
		// FIXME {end} {code copied from M2CodeGenerator.visit(ASTStmt) - refactor}
		
		if (numArgs == 2) {
			M2AsmNode arg1Node = (M2AsmNode) node.jjtGetChild(1);  //child 0 was processed, already
			M2AsmNode arg2Node = (M2AsmNode) node.jjtGetChild(2);
			
			//LOD immediate, anything
			//STOR immediate, anything
			if (arg1Node instanceof ASTInteger || arg1Node instanceof ASTChar) {
				if (op.name().startsWith("LOD") || op.name().startsWith("STOR")) {
					errorInvalidOp(op, arg1Node.value, arg2Node.value);
				}
			}
			
			// LOD Reg, Reg
			if ((arg1Node instanceof ASTRegInt || arg1Node instanceof ASTRegFloat) &&
				(arg2Node instanceof ASTRegInt || arg2Node instanceof ASTRegFloat)
			) {
				if (op.name().startsWith("LOD") || op.name().startsWith("STOR")) {
					errorInvalidOp(op, arg1Node.value, arg2Node.value);
				}
			}
		}
	}
	
}
