package br.unipe.m2asm.parse;

import br.unipe.m2asm.codegen.SymbolTable;


/**
 * @author Odilon
 *
 */
public abstract class M2AsmParserVisitorAdapter implements M2AsmParserVisitor {

	/* (non-Javadoc)
	 * @see br.unipe.m2asm.parse.M2AsmParserVisitor#visit(br.unipe.m2asm.parse.SimpleNode, java.lang.Object)
	 */
	@Override
	public void visit(SimpleNode node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTProg node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTSegment node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTStmt node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTOpcode node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTDeclarator node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTValues node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTId node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTInteger node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTChar node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTRegInt node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTRegFloat node, SymbolTable data) {
		// TODO Auto-generated method stub
	}

	@Override
	public void visit(ASTLabel node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTMemRef node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTStr node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTDeclaratorNonInit node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTMemOffset node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTMemSize node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTPseudoStmt node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void visit(ASTStackDecl node, SymbolTable data) {
		node.childrenAccept(this, data);
	}

	@Override
	public void visit(ASTInclude node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTDef node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visit(ASTMacro node, SymbolTable data) {
		// TODO Auto-generated method stub
		
	}
}
