package br.unipe.m2asm.codegen;

import br.unipe.m2asm.parse.ASTChar;
import br.unipe.m2asm.parse.ASTDef;
import br.unipe.m2asm.parse.ASTId;
import br.unipe.m2asm.parse.ASTInteger;
import br.unipe.m2asm.parse.ASTProg;
import br.unipe.m2asm.parse.ASTStmt;
import br.unipe.m2asm.parse.M2AsmNode;
import br.unipe.m2asm.parse.M2AsmParserTreeConstants;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;

/**
 * Resolves references to macros, substituting their values in the AST.
 * TODO  Study possibility of using this same approach to LabelResolver...
 * 
 * @author Odilon
 *
 */
public class MacroResolver extends M2AsmParserVisitorAdapter {

	private int pass = 1;
	
	@Override
	public void visit(ASTProg node, SymbolTable data) {
		super.visit(node, data);
		pass++;
		if (pass > 2) return;
		// resolve as macros
		visit(node, data);
	}
	
	/**
	 * Simple macro, just a "define"  (%DEF  id  value)
	 */
	@Override
	public void visit(ASTDef node, SymbolTable data) {
		super.visit(node, data);
		if (pass == 1) {
			ASTId idNode = (ASTId) node.jjtGetChild(0);
			M2AsmNode valNode = (M2AsmNode) node.jjtGetChild(1);
			data.addDef(idNode.value, valNode.value);
		}
	}

	@Override
	public void visit(ASTStmt node, SymbolTable data) {
		super.visit(node, data);
		if (pass == 2) {
			int n = node.jjtGetNumChildren();
			for (int i = 0; i < n; i++) {
				M2AsmNode child = (M2AsmNode) node.jjtGetChild(i);
				if (data.isDef(child.value)) {
					String val = data.resolveDef(child.value);
					M2AsmNode newNode = null;
					if (isInteger(val)) {
						newNode = new ASTInteger(M2AsmParserTreeConstants.JJTINTEGER);
					}
					else if (isChar(val)) {
						newNode = new ASTChar(M2AsmParserTreeConstants.JJTCHAR);
					}
					if (newNode != null) {
						newNode.value = val;
						replace(child, newNode);
					}
				}
			}
		}
	}
	
	private boolean isVarName(String s) {
		boolean b = Character.isJavaIdentifierStart(s.charAt(0));
		int n = s.length();
		for (int i = 1; i < n; i++) {
			b &= Character.isJavaIdentifierPart(s.charAt(i));
		}
		return b;
	}
	
	private boolean isInteger(String s) {
		boolean b = Character.isDigit(s.charAt(0));
		int n = s.length();
		for (int i = 1; i < n; i++) {
			b &= Character.isDigit(s.charAt(i));
		}
		return b;
	}
	
	private boolean isChar(String s) {
		return s.length() == 3 && s.charAt(0) == '\'' && s.charAt(2) == '\'';
	}
	
	/**
	 * FIXME  código replicado de IncludeResolver.java
	 * Substitui um nó por outro, como filho do nó pai.
	 * A comparação entre os nós é feita pelo endereço (referências idênticas)
	 *   
	 * @param oldNode
	 * @param newNode
	 */
	private void replace(M2AsmNode oldNode, M2AsmNode newNode) {
		M2AsmNode parent = (M2AsmNode) oldNode.jjtGetParent();
		// replace node in parent
		M2AsmNode child, thisNode = oldNode;
		for (int i = 0; i < parent.jjtGetNumChildren(); i++) {
			child = (M2AsmNode) parent.jjtGetChild(i);
			if (child == thisNode) {
				parent.jjtAddChild(newNode, i);   //jjtAddChild em um índice existente efetivamente substitui o conteudo
				break;					
			}
		}
	}
}
