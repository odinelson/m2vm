package br.unipe.m2asm.util;


/**
 * @author Odilon
 *
 */
public class AsmError extends RuntimeException {
	
	private static final long serialVersionUID = 1318358251925939964L;

	public AsmError(String msg) {
		super(msg);
	}
	
	public AsmError(String msg, Object... args) {
		///super(String.format(msg, args));
		super(Util.format(msg, args));
	}
}
