/* Generated By:JJTree: Do not edit this line. ASTDef.java Version 4.3 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
package br.unipe.m2asm.parse;

public
@SuppressWarnings("all")
class ASTDef extends M2AsmNode {
  public ASTDef(int id) {
    super(id);
  }

  public ASTDef(M2AsmParser p, int id) {
    super(p, id);
  }


  /** Accept the visitor. **/
  public void jjtAccept(M2AsmParserVisitor visitor, br.unipe.m2asm.codegen.SymbolTable data) {
    visitor.visit(this, data);
  }
}
/* JavaCC - OriginalChecksum=8a74ecaee3fe2e7b432b44f5060b6b4a (do not edit this line) */
