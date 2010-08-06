package br.unipe.m2asm.parse;

/**
 * @author Odilon
 *
 */
public class M2AsmNode extends SimpleNode {

	public String value;
	
	public M2AsmNode(int i) {
		super(i);
		// TODO Auto-generated constructor stub
	}

	public M2AsmNode(M2AsmParser p, int id) {
	    super(p, id);
	}

	@Override
	public String toString() {
		return value  == null ? super.toString() : String.format("%s (%s)", super.toString(), value);
	}
	
}
