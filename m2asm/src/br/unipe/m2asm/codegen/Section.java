package br.unipe.m2asm.codegen;

/**
 * Represents a section of the source code, where labels are created.
 * This is *not* the same as segments of the actual assembled program.
 * (E.g. : DATA can be Data segment or Uninialized data segment)
 * 
 * @author Odilon
 *
 */
public enum Section {
	CODE, DATA
}
