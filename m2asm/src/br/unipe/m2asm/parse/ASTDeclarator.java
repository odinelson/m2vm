/* Generated By:JJTree: Do not edit this line. ASTDeclarator.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
package br.unipe.m2asm.parse;

public
@SuppressWarnings("all")
class ASTDeclarator extends M2AsmNode {
  public ASTDeclarator(int id) {
    super(id);
  }

  public ASTDeclarator(M2AsmParser p, int id) {
    super(p, id);
  }


  /** Accept the visitor. **/
  public void jjtAccept(M2AsmParserVisitor visitor, br.unipe.m2asm.codegen.SymbolTable data) {
    visitor.visit(this, data);
  }
}
/* JavaCC - OriginalChecksum=f38903f46ff96f56e15f5ed1de47db7e (do not edit this line) */