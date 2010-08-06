package br.unipe.m2asm.machine;

/**
 * Represents a section od the source code.
 * Might not be equivalent the the segments of the actual assembled program.
 * (E.g. : DATA can be Data segment or Uninialized data segment)
 * 
 * @author Odilon
 *
 */
public enum Section {
	CODE, DATA, STACK
}
