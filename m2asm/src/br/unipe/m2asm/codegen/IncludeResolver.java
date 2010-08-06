package br.unipe.m2asm.codegen;

import br.unipe.m2asm.Main;
import br.unipe.m2asm.parse.ASTInclude;
import br.unipe.m2asm.parse.ASTProg;
import br.unipe.m2asm.parse.ASTStr;
import br.unipe.m2asm.parse.M2AsmNode;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;

/**
 * @author Odilon
 *
 */
public class IncludeResolver extends M2AsmParserVisitorAdapter {

	@Override
	public void visit(ASTInclude node, SymbolTable data) {
		super.visit(node, data);
		ASTStr strNode = (ASTStr) node.jjtGetChild(0);
		String fileName = strNode.value + ".m2i";  //FIXME detect if extension is not given
		System.out.println("Including fileName: " + fileName);
		try {
			ASTProg newNode = Main.parse(fileName);
			replace(node, newNode);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
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
