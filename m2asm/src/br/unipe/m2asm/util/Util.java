package br.unipe.m2asm.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.Formatter;
import java.util.LinkedHashSet;
import java.util.Locale;
import java.util.Set;

import br.unipe.m2asm.machine.Opcode;
import br.unipe.m2asm.machine.Reg;

/**
 * @author Odilon
 *
 */
public class Util {
	
	private static Set<String> regNames;
	private static Set<String> opcodeNames;
	
	static {
		regNames = new LinkedHashSet<String>();
		for (Reg r : Reg.values()) {
			regNames.add(r.name());
		}
		regNames = Collections.unmodifiableSet(regNames);
		
		opcodeNames = new LinkedHashSet<String>();
		for (Opcode op : Opcode.values()) {
			opcodeNames.add(op.getMnemonic());
		}
		opcodeNames = Collections.unmodifiableSet(opcodeNames);
	}
	
	private Util() { }
	
	public static void error(String msg) {
		throw new AsmError(msg);
	}
	
	public static void error(String msg, Object... args) {
		throw new AsmError(msg, args);
	}
	
	public static boolean isRegName(String name) {
		return regNames.contains(name);
	}
	
	public static boolean isOpcodeName(String name) {
		return opcodeNames.contains(name);
	}
	
	public static void checkReservedName(String name, String msg, int lineNumber) {
		if (isRegName(name) || isOpcodeName(name)) {
			error("Reserved identifier \"%s\" used as %s at line %d", name, msg, lineNumber);
		}
	}
	
	public static boolean checkMaybeImm(String imm) {
		return (imm.length() >= 1 && startsWithDigit(imm))
			|| (imm.length() >= 2 && imm.charAt(0) == '-' && hasDigitAt(imm, 1));
	}
	
	private static boolean startsWithDigit(String s) {
		return hasDigitAt(s, 0);
	}
	
	private static boolean hasDigitAt(String s, int idx) {
		return Character.isDigit(s.charAt(idx));
	}
	
	public static boolean checkMaybeLabel(String label) {
		return label.length() > 1 && label.charAt(0) == '@';
	}
	
	public static String validateLabelDecl(String label, int lineNumber) {
		int n = label.length();
		if (n < 3 || label.charAt(0) != '@' || label.charAt(n-1) != ':') {
			error("Invalid label: %s, at line %d", label, lineNumber);
		}
		return label.substring(0, n-1);  //does not include the ':' terminator
	}
	
	public static void validateLabelAsArgument(String label, int lineNumber) {
		int n = label.length();
		if (n < 2 || label.charAt(0) != '@') {
			error("Invalid label: %s, at line %d", label, lineNumber);
		}
	}
	
	public static String[] copyFromIndex(String strs[], int idx) {
		final int n = strs.length - idx;
		String[] newStrs = new String[n];
		// Copy all, but the 1st element
		System.arraycopy(strs, idx, newStrs, 0, n);
		return newStrs;
	}
	
	public static Set<String> processList(String[] tokens, int lineNumber, String elementDescription) {
		return processList(tokens, lineNumber, elementDescription, true);
	}
	
	public static Set<String> processListNoCheck(String[] tokens, int lineNumber, String elementDescription) {
		return processList(tokens, lineNumber, elementDescription, false);
	}
	
	public static Set<String> processList(String[] tokens, int lineNumber, String elementDescription, boolean checkReserved) {
		Set<String> processed = new LinkedHashSet<String>();
		for (int i = 0; i < tokens.length; i++) {
			if (i % 2 != 0 && !tokens[i].equals(",")) {  //layout: item,item ; so that tokens[0] is 1st elem and each even index is a comma...
				error("Syntax error at line %d ; comma missing", lineNumber);
			}
			else if (i == tokens.length-1 && tokens[i].equals(",")) {
				error("Syntax error at line %d; %s missing", lineNumber, elementDescription);
			}
			else if (i % 2 == 0 && tokens[i].equals(",")) {
				error("Syntax error at line %d ; %s missing", lineNumber, elementDescription);
			}
			else if (!tokens[i].equals(",")) {
				if (checkReserved)
					checkReservedName(tokens[i], elementDescription, lineNumber);
				if (processed.contains(tokens[i])) {
					error("Duplicated %s \"%s\" at line %d", elementDescription, tokens[i], lineNumber);
				}
				processed.add(tokens[i]);
			}
		}
		return processed;
	}
	
	/**
	 * Opens a file on disk and returns its contents as a String
	 * @param filePath
	 * @return
	 * @throws IOException
	 */
	public static String openFile(String filePath) throws IOException {
		FileInputStream input = new FileInputStream(filePath);

		byte[] fileData = new byte[(int) new File(filePath).length()];

		input.read(fileData);
		input.close();

		return new String(fileData);
	}

	public static void createTextFile(String filePath, String  contents) throws IOException {
		FileWriter output = new FileWriter(filePath);
		output.write(contents);
		output.flush();
		output.close();
	}
	
	public static String replaceFileExt(String filePath, String oldExt, String newExt) {
		String tmp = filePath.substring(0, filePath.indexOf("." + oldExt));
		return tmp + "." + newExt;
	}
	
	/**
	 * Converts a string representation of a byte (in either hex or decimal)
	 * into a byte value.
	 * @param s
	 * @return
	 */
	public static byte strToByte(String s) {
		/*int radix = 10;
		if (s.startsWith("0x")) {
			radix = 16;
			s = s.substring(2); //remove prefix
		}
		return Byte.parseByte(s, radix);*/
		int i = strToInt(s);
		return (byte)i;
	}
	
	/**
	 * Converts a string representation of a short (in either hex or decimal)
	 * into a short value.
	 * @param s
	 * @return
	 */
	public static short strToShort(String s) {
		int i = strToInt(s);
		return (short)i;
	}
	
	/**
	 * Converts a string representation of an integer (in either hex or decimal)
	 * into an int value.
	 * @param s
	 * @return
	 */
	public static int strToInt(String s) {
		int radix = 10;
		if (s.startsWith("0x")) {
			radix = 16;
			s = s.substring(2); //remove prefix
		}
		return Integer.parseInt(s, radix);
	}
	
	// Workaround for GCJ... it does not have String.format
	public static String format(String msg, Object... args) {
		Formatter f = new Formatter(Locale.getDefault());
	    return f.format(msg, args).toString();
	}
	
	/**
	 * For debugging
	 * @param bytes
	 */
	public static String toHexString(byte[] bytes) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < bytes.length; i++) {
			sb.append(Util.format("0x%02X ", bytes[i]));
		}
		return sb.toString();
	}
	
	/**
	 * From: http://code.google.com/p/fluid-forms-libs Returns a String
	 * representation of the bits in a byte. The String begins with the most
	 * significant bit in the byte. The bits are represented as '0' and '1's in
	 * the String.
	 * 
	 * @param n
	 *            the byte to be converted.
	 * @return a string representation of the argument in base 2.
	 **/
	public static String toBitString(final byte n) {
		final int tmp = n;
		final StringBuffer sb = new StringBuffer(8);
		for (int i = 7; i >= 0; i--) {
			if ((tmp & (1 << i)) >> i == 1) {
				sb.append('1');
			} else {
				sb.append('0');
			}
		}
		return sb.toString();
	}

	/**
	 * From: http://code.google.com/p/fluid-forms-libs Returns a String
	 * representation of the bits in a byte array. The String begins with the
	 * representation of the first byte in the array (byte[0]). The most
	 * significant comes first in each byte. The bits are represented by '0' and
	 * '1's in the String.
	 * 
	 * @param ba
	 *            the byte[] to be converted.
	 * @return a string representation of the argument in base 2.
	 **/
	public static String toBitString(final byte[] ba) {
		return toBitString(ba, null);
	}

	/**
	 * From: http://code.google.com/p/fluid-forms-libs Returns a String
	 * representation of the bits in a byte array. The String begins with the
	 * representation of the first byte in the array (byte[0]) Bytes are
	 * separated by byteSpace. The most significant comes first in each byte.
	 * The bits are represented by '0' and '1's in the String.
	 * 
	 * @param ba
	 *            the byte[] to be converted.
	 * @param byteSpace
	 *            the spacing to use between each byte.
	 * @return a string representation of the argument in base 2.
	 **/
	public static String toBitString(final byte[] ba, final String byteSpace) {
		final StringBuffer sb = new StringBuffer();
		for (int i = 0; i < ba.length; i++) {
			sb.append(toBitString(ba[i]));
			if (byteSpace != null && i < ba.length - 1) {
				sb.append(byteSpace);
			}
		}
		return sb.toString();
	}
}
