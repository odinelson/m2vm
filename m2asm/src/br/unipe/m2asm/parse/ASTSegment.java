/* Generated By:JJTree: Do not edit this line. ASTSegment.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
package br.unipe.m2asm.parse;

public
@SuppressWarnings("all")
class ASTSegment extends M2AsmNode {
  public ASTSegment(int id) {
    super(id);
  }

  public ASTSegment(M2AsmParser p, int id) {
    super(p, id);
  }


  /** Accept the visitor. **/
  public void jjtAccept(M2AsmParserVisitor visitor, br.unipe.m2asm.codegen.SymbolTable data) {
    visitor.visit(this, data);
  }
}
/* JavaCC - OriginalChecksum=26d2c7dbef606f5d448e28b42f6211d9 (do not edit this line) */