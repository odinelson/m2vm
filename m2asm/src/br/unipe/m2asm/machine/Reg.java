package br.unipe.m2asm.machine;

public enum Reg {
	R0((byte)0), R1((byte)1), R2((byte)2), R3((byte)3), R4((byte)4), R5((byte)5),
	JR((byte)6), IR((byte)7), MR((byte)8), DT((byte)9), UD((byte)10), ST((byte)11),
	SB((byte)12), SP((byte)13), FP((byte)14), IP((byte)15),
	F0((byte)0), F1((byte)1), F2((byte)2), F3((byte)3), F4((byte)4), F5((byte)5);
	
	private final byte value;
	
	private Reg(byte value) {
		this.value = value;
	}
	
	public byte getValue() {
		return value;
	}

	public boolean isFloat() {
		return this != FP && this.name().charAt(0) == 'F';
	}
}
