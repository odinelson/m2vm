package br.unipe.m2asm.semant;

import br.unipe.m2asm.codegen.SymbolTable;
import br.unipe.m2asm.parse.ASTProg;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;

/**
 * Facade to some (basic) semantic checks
 * 
 * @author Odilon
 *
 */
public class SemanticAnalyzer {
	public void analyse(ASTProg root, SymbolTable symTab) {
		M2AsmParserVisitorAdapter operandChecker = new OperandChecker();
		operandChecker.visit(root, symTab);
	}
}
