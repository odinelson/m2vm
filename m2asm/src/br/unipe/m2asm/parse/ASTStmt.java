/* Generated By:JJTree: Do not edit this line. ASTStmt.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
package br.unipe.m2asm.parse;

public
@SuppressWarnings("all")
class ASTStmt extends M2AsmNode {
  public ASTStmt(int id) {
    super(id);
  }

  public ASTStmt(M2AsmParser p, int id) {
    super(p, id);
  }


  /** Accept the visitor. **/
  public void jjtAccept(M2AsmParserVisitor visitor, br.unipe.m2asm.codegen.SymbolTable data) {
    visitor.visit(this, data);
  }
}
/* JavaCC - OriginalChecksum=3b9c0932a352f5b671ad062126b2153e (do not edit this line) */
