package br.unipe.m2asm.machine;

public enum Opcode {
	NOP("NOP"),			//0 arg; No Operation
	HALT("HALT"),		//0 arg; Halt VM
	INC("INC"),   //1 arg; Increment value in Integer Register
	DEC("DEC"),   //1 arg; Decrement value in Integer Register
	ADD("ADD"),   //2 arg; Add values in Integer Registers
	ADDI("ADD"),   //2 arg; Add imm to Integer Register
	SUB("SUB"),   //2 arg; Subtract values in Integer Registers
	MUL("MUL"),   //2 arg; Multiply values in Integer Registers
	DIV("DIV"),   //2 arg; Divide values in Integer Registers
	NEG("NEG"),   //1 arg; Negate value in Integer Register
	ADDF("ADD"),   //2 arg; Add values in Floating-point Registers
	SUBF("SUB"),   //2 arg; Subtract values in Floating-point Registers
	MULF("MUL"),   //2 arg; Multiply values in Floating-point Registers
	DIVF("DIV"),   //2 arg; Divide values in Floating-point Registers
	NEGF("NEG"),   //1 arg; Negate value in Floating-point Register
	AND("AND"),   //2 arg; Logical AND values in Integer Registers
	ANDI("AND"),   //2 arg; Logical AND Integer Register & imm
	OR("OR"),   //2 arg; Logical OR values in Integer Registers
	ORI("OR"),   //2 arg; Logical OR Integer Register & imm
	XOR("XOR"),   //2 arg; Logical XOR values in Integer Registers
	XORI("XOR"),   //2 arg; Logical XOR Integer Register & imm
	NOT("NOT"),   //1 arg; Logical NOT value in Integer Register
	SHL("SHL"),   //2 arg; Left-shift by imm bytes value in Integer Register
	SHR("SHR"),   //2 arg; Right-shift by imm bytes value in Integer Register
	CPY("CPY"),   //2 arg; Copy value between Integer Registers
	CPYF("CPY"),   //2 arg; Copy value between Floating-point Registers
	CPYFR("CPY"),   //2 arg; Copy value from Integer Register to Floating-point Register
	CPYRF("CPY"),   //2 arg; Copy value from Floating-point Register to Integer Register
	CMP("CMP"),   //2 arg; Compare values in Integer Registers; store result in FLAGS
	CMPI("CMP"),   //2 arg; Compare value in Integer Register & imm; store result in FLAGS
	CMPF("CMP"),   //2 arg; Compare values in Float Registers; store result in FLAGS
	LOD("LOD"),   //2 arg; Load word to Integer Register1 from RAM, indexed (address given by Register2+offset)
	LODB("LOD"),   //2 arg; Load byte to Integer Register1 from RAM, indexed (address given by Register2+offset)
	LODF("LOD"),   //2 arg; Load value to Floating-point Register1 from RAM, indexed (address given by Int Register2+offset)
	LODI("LOD"),   //2 arg; Load halfword immediate (sign-extended) to Integer Register
	LODFI("LOD"),   //2 arg; Load halfword immediate (sign-extended) to Floating-point Register
	STOR("STOR"),   //2 arg; Store word in Integer Register2 to RAM, indexed (address given by Register1+offset)
	STORB("STOR"),   //2 arg; Store byte in Integer Register2 to RAM, indexed (address given by Register1+offset)
	STORF("STOR"),   //2 arg; Store value (dword-sized) in Floating-point Register2 to RAM, indexed (address given by Register1+offset)
	JMP("JMP"),   //1 arg; Jump to address (IP relative)
	JE("JE"),   //1 arg; Jump to address (IP relative) if values in last comparison are Equal
	JNE("JNE"),   //1 arg; Jump to address (IP relative) if values in last comparison are Not Equal
	JL("JL"),   //1 arg; Jump to address (IP relative) if 1st value is Less than 2nd value in last comparison
	JLE("JLE"),   //1 arg; Jump to address (IP relative) if 1st value is Less than or Equal to 2nd value in last comparison
	JG("JG"),   //1 arg; Jump to address (IP relative) if 1st value is Greater than 2nd value in last comparison
	JGE("JGE"),   //1 arg; Jump to address (IP relative) if 1st value is Greater than or Equal to 2nd value in last comparison
	INT("INT"),   //1 arg; Execute Interrupt. (Interrupt number is given in immediate arg - function is in IR)
	CALL("CALL"),   //1 arg; Call procedure at address (IP relative)
	RET("RET"),   //0 arg; Return from procedure
	PUSH("PUSH"),   //1 arg; Push dword value in Integer Register to stack segment
	POP("POP"),   //1 arg; Pop dword value in stack segment to Integer Register
	PUSHF("PUSH"),   //1 arg; Push value in Floating-point Register to stack segment
	POPF("POP");   //1 arg; Pop value in stack segment to Floating-point Register
	
	private final String mnemonic;
	
	private Opcode(String mnemonic) {
		this.mnemonic = mnemonic;
	}

	public byte getCode() {
		return (byte) this.ordinal();
	}

	public String getMnemonic() {
		return mnemonic;
	}
}
