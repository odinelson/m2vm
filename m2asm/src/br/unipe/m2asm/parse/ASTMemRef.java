/* Generated By:JJTree: Do not edit this line. ASTMemRef.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
package br.unipe.m2asm.parse;

public
@SuppressWarnings("all")
class ASTMemRef extends M2AsmNode {
  public ASTMemRef(int id) {
    super(id);
  }

  public ASTMemRef(M2AsmParser p, int id) {
    super(p, id);
  }


  /** Accept the visitor. **/
  public void jjtAccept(M2AsmParserVisitor visitor, br.unipe.m2asm.codegen.SymbolTable data) {
    visitor.visit(this, data);
  }
}
/* JavaCC - OriginalChecksum=b4dbf893eafc49eb5f2758bbb36d31fc (do not edit this line) */
