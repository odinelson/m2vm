/* Generated By:JJTree&JavaCC: Do not edit this line. M2AsmParser.java */
package br.unipe.m2asm.parse;

@SuppressWarnings("all")
public class M2AsmParser/*@bgen(jjtree)*/implements M2AsmParserTreeConstants, M2AsmParserConstants {/*@bgen(jjtree)*/
  protected JJTM2AsmParserState jjtree = new JJTM2AsmParserState();

  final public ASTProg Prog() throws ParseException {
                  /*@bgen(jjtree) Prog */
  ASTProg jjtn000 = new ASTProg(JJTPROG);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      label_1:
      while (true) {
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case NEWLINE:
          ;
          break;
        default:
          jj_la1[0] = jj_gen;
          break label_1;
        }
        jj_consume_token(NEWLINE);
      }
      label_2:
      while (true) {
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case INCLUDE:
        case DEF:
        case MACRO:
          ;
          break;
        default:
          jj_la1[1] = jj_gen;
          break label_2;
        }
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case INCLUDE:
          Include();
          break;
        case DEF:
          Def();
          break;
        case MACRO:
          Macro();
          break;
        default:
          jj_la1[2] = jj_gen;
          jj_consume_token(-1);
          throw new ParseException();
        }
        label_3:
        while (true) {
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case NEWLINE:
            ;
            break;
          default:
            jj_la1[3] = jj_gen;
            break label_3;
          }
          jj_consume_token(NEWLINE);
        }
      }
      label_4:
      while (true) {
        Segment();
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case CODESEG:
        case DATASEG:
          ;
          break;
        default:
          jj_la1[4] = jj_gen;
          break label_4;
        }
      }
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case STACKSEG:
        StackDecl();
        break;
      default:
        jj_la1[5] = jj_gen;
        ;
      }
            jjtree.closeNodeScope(jjtn000, true);
            jjtc000 = false;
            {if (true) return jjtn000;}
    } catch (Throwable jjte000) {
                            if (jjtc000) {
                              jjtree.clearNodeScope(jjtn000);
                              jjtc000 = false;
                            } else {
                              jjtree.popNode();
                            }
                            if (jjte000 instanceof RuntimeException) {
                              {if (true) throw (RuntimeException)jjte000;}
                            }
                            if (jjte000 instanceof ParseException) {
                              {if (true) throw (ParseException)jjte000;}
                            }
                            {if (true) throw (Error)jjte000;}
    } finally {
                            if (jjtc000) {
                              jjtree.closeNodeScope(jjtn000, true);
                            }
    }
    throw new Error("Missing return statement in function");
  }

  final public void Segment() throws ParseException {
                  /*@bgen(jjtree) Segment */
                   ASTSegment jjtn000 = new ASTSegment(JJTSEGMENT);
                   boolean jjtc000 = true;
                   jjtree.openNodeScope(jjtn000);Token t;
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case CODESEG:
        t = jj_consume_token(CODESEG);
        break;
      case DATASEG:
        t = jj_consume_token(DATASEG);
        break;
      default:
        jj_la1[6] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
      label_5:
      while (true) {
        jj_consume_token(NEWLINE);
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case NEWLINE:
          ;
          break;
        default:
          jj_la1[7] = jj_gen;
          break label_5;
        }
      }
            jjtn000.value = t.image.substring(1);
      StmtList();
    } catch (Throwable jjte000) {
            if (jjtc000) {
              jjtree.clearNodeScope(jjtn000);
              jjtc000 = false;
            } else {
              jjtree.popNode();
            }
            if (jjte000 instanceof RuntimeException) {
              {if (true) throw (RuntimeException)jjte000;}
            }
            if (jjte000 instanceof ParseException) {
              {if (true) throw (ParseException)jjte000;}
            }
            {if (true) throw (Error)jjte000;}
    } finally {
            if (jjtc000) {
              jjtree.closeNodeScope(jjtn000, true);
            }
    }
  }

/*
 * The stack segment is treated differently; in the executable format, it is
 * a segment, but on the source, it is just the declaration of the stack size.
*/
  final public void StackDecl() throws ParseException {
                    /*@bgen(jjtree) StackDecl */
  ASTStackDecl jjtn000 = new ASTStackDecl(JJTSTACKDECL);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      jj_consume_token(STACKSEG);
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NEWLINE:
        label_6:
        while (true) {
          jj_consume_token(NEWLINE);
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case NEWLINE:
            ;
            break;
          default:
            jj_la1[8] = jj_gen;
            break label_6;
          }
        }
        break;
      default:
        jj_la1[9] = jj_gen;
        ;
      }
      DeclaratorNonInit();
      Integer();
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NEWLINE:
        label_7:
        while (true) {
          jj_consume_token(NEWLINE);
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case NEWLINE:
            ;
            break;
          default:
            jj_la1[10] = jj_gen;
            break label_7;
          }
        }
        break;
      case 0:
        jj_consume_token(0);
        break;
      default:
        jj_la1[11] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
    } catch (Throwable jjte000) {
            if (jjtc000) {
              jjtree.clearNodeScope(jjtn000);
              jjtc000 = false;
            } else {
              jjtree.popNode();
            }
            if (jjte000 instanceof RuntimeException) {
              {if (true) throw (RuntimeException)jjte000;}
            }
            if (jjte000 instanceof ParseException) {
              {if (true) throw (ParseException)jjte000;}
            }
            {if (true) throw (Error)jjte000;}
    } finally {
            if (jjtc000) {
              jjtree.closeNodeScope(jjtn000, true);
            }
    }
  }

  final public void StmtList() throws ParseException {
    label_8:
    while (true) {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NOP:
      case HALT:
      case INC:
      case DEC:
      case ADD:
      case SUB:
      case MUL:
      case DIV:
      case NEG:
      case AND:
      case OR:
      case XOR:
      case NOT:
      case SHL:
      case SHR:
      case CPY:
      case CMP:
      case LOD:
      case STOR:
      case JMP:
      case JE:
      case JNE:
      case JL:
      case JLE:
      case JG:
      case JGE:
      case INT:
      case CALL:
      case RET:
      case PUSH:
      case POP:
      case INCLUDE:
      case DB:
      case DW:
      case RESB:
      case RESW:
      case IDENTIFIER:
        ;
        break;
      default:
        jj_la1[12] = jj_gen;
        break label_8;
      }
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case IDENTIFIER:
        Label();
        label_9:
        while (true) {
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case NEWLINE:
            ;
            break;
          default:
            jj_la1[13] = jj_gen;
            break label_9;
          }
          jj_consume_token(NEWLINE);
        }
        break;
      default:
        jj_la1[14] = jj_gen;
        ;
      }
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NOP:
      case HALT:
      case INC:
      case DEC:
      case ADD:
      case SUB:
      case MUL:
      case DIV:
      case NEG:
      case AND:
      case OR:
      case XOR:
      case NOT:
      case SHL:
      case SHR:
      case CPY:
      case CMP:
      case LOD:
      case STOR:
      case JMP:
      case JE:
      case JNE:
      case JL:
      case JLE:
      case JG:
      case JGE:
      case INT:
      case CALL:
      case RET:
      case PUSH:
      case POP:
        Stmt();
        break;
      case DB:
      case DW:
      case RESB:
      case RESW:
        PseudoStmt();
        break;
      case INCLUDE:
        Include();
        break;
      default:
        jj_la1[15] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NEWLINE:
        label_10:
        while (true) {
          jj_consume_token(NEWLINE);
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case NEWLINE:
            ;
            break;
          default:
            jj_la1[16] = jj_gen;
            break label_10;
          }
        }
        break;
      case 0:
        jj_consume_token(0);
        break;
      default:
        jj_la1[17] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
    }
  }

  final public void Stmt() throws ParseException {
               /*@bgen(jjtree) Stmt */
  ASTStmt jjtn000 = new ASTStmt(JJTSTMT);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      Opcode();
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case INTEGER_LITERAL:
      case CHAR_LITERAL:
      case REG_INT:
      case REG_FLOAT:
      case IDENTIFIER:
      case 61:
        Arg();
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case 59:
          jj_consume_token(59);
          Arg();
          break;
        default:
          jj_la1[18] = jj_gen;
          ;
        }
        break;
      default:
        jj_la1[19] = jj_gen;
        ;
      }
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void PseudoStmt() throws ParseException {
                     /*@bgen(jjtree) PseudoStmt */
  ASTPseudoStmt jjtn000 = new ASTPseudoStmt(JJTPSEUDOSTMT);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case DB:
      case DW:
        Declarator();
        Values();
        break;
      case RESB:
      case RESW:
        DeclaratorNonInit();
        Integer();
        break;
      default:
        jj_la1[20] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Include() throws ParseException {
                  /*@bgen(jjtree) Include */
  ASTInclude jjtn000 = new ASTInclude(JJTINCLUDE);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      jj_consume_token(INCLUDE);
      Str();
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Def() throws ParseException {
              /*@bgen(jjtree) Def */
  ASTDef jjtn000 = new ASTDef(JJTDEF);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      jj_consume_token(DEF);
      Id();
      Value();
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Macro() throws ParseException {
                /*@bgen(jjtree) Macro */
                 ASTMacro jjtn000 = new ASTMacro(JJTMACRO);
                 boolean jjtc000 = true;
                 jjtree.openNodeScope(jjtn000);Token t;
    try {
      jj_consume_token(MACRO);
      Id();
      StmtList();
      jj_consume_token(ENDMACRO);
      Id();
    } catch (Throwable jjte000) {
            if (jjtc000) {
              jjtree.clearNodeScope(jjtn000);
              jjtc000 = false;
            } else {
              jjtree.popNode();
            }
            if (jjte000 instanceof RuntimeException) {
              {if (true) throw (RuntimeException)jjte000;}
            }
            if (jjte000 instanceof ParseException) {
              {if (true) throw (ParseException)jjte000;}
            }
            {if (true) throw (Error)jjte000;}
    } finally {
            if (jjtc000) {
              jjtree.closeNodeScope(jjtn000, true);
            }
    }
  }

  final public void Opcode() throws ParseException {
                 /*@bgen(jjtree) Opcode */
                  ASTOpcode jjtn000 = new ASTOpcode(JJTOPCODE);
                  boolean jjtc000 = true;
                  jjtree.openNodeScope(jjtn000);Token t;
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case NOP:
        t = jj_consume_token(NOP);
        break;
      case HALT:
        t = jj_consume_token(HALT);
        break;
      case INC:
        t = jj_consume_token(INC);
        break;
      case DEC:
        t = jj_consume_token(DEC);
        break;
      case ADD:
        t = jj_consume_token(ADD);
        break;
      case SUB:
        t = jj_consume_token(SUB);
        break;
      case MUL:
        t = jj_consume_token(MUL);
        break;
      case DIV:
        t = jj_consume_token(DIV);
        break;
      case NEG:
        t = jj_consume_token(NEG);
        break;
      case AND:
        t = jj_consume_token(AND);
        break;
      case OR:
        t = jj_consume_token(OR);
        break;
      case XOR:
        t = jj_consume_token(XOR);
        break;
      case NOT:
        t = jj_consume_token(NOT);
        break;
      case SHL:
        t = jj_consume_token(SHL);
        break;
      case SHR:
        t = jj_consume_token(SHR);
        break;
      case CPY:
        t = jj_consume_token(CPY);
        break;
      case CMP:
        t = jj_consume_token(CMP);
        break;
      case LOD:
        t = jj_consume_token(LOD);
        break;
      case STOR:
        t = jj_consume_token(STOR);
        break;
      case JMP:
        t = jj_consume_token(JMP);
        break;
      case JE:
        t = jj_consume_token(JE);
        break;
      case JNE:
        t = jj_consume_token(JNE);
        break;
      case JL:
        t = jj_consume_token(JL);
        break;
      case JLE:
        t = jj_consume_token(JLE);
        break;
      case JG:
        t = jj_consume_token(JG);
        break;
      case JGE:
        t = jj_consume_token(JGE);
        break;
      case INT:
        t = jj_consume_token(INT);
        break;
      case CALL:
        t = jj_consume_token(CALL);
        break;
      case RET:
        t = jj_consume_token(RET);
        break;
      case PUSH:
        t = jj_consume_token(PUSH);
        break;
      case POP:
        t = jj_consume_token(POP);
        break;
      default:
        jj_la1[21] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image.toUpperCase();
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Arg() throws ParseException {
    switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
    case IDENTIFIER:
      Id();
      break;
    case INTEGER_LITERAL:
      Integer();
      break;
    case REG_INT:
      RegInt();
      break;
    case REG_FLOAT:
      RegFloat();
      break;
    case CHAR_LITERAL:
      Char();
      break;
    case 61:
      MemRef();
      break;
    default:
      jj_la1[22] = jj_gen;
      jj_consume_token(-1);
      throw new ParseException();
    }
  }

  final public void Declarator() throws ParseException {
                     /*@bgen(jjtree) Declarator */
                      ASTDeclarator jjtn000 = new ASTDeclarator(JJTDECLARATOR);
                      boolean jjtc000 = true;
                      jjtree.openNodeScope(jjtn000);Token t;
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case DB:
        t = jj_consume_token(DB);
        break;
      case DW:
        t = jj_consume_token(DW);
        break;
      default:
        jj_la1[23] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
            jjtree.closeNodeScope(jjtn000, true);
            jjtc000 = false;
            jjtn000.value = t.image.toUpperCase();
    } finally {
            if (jjtc000) {
              jjtree.closeNodeScope(jjtn000, true);
            }
    }
  }

  final public void DeclaratorNonInit() throws ParseException {
                            /*@bgen(jjtree) DeclaratorNonInit */
                             ASTDeclaratorNonInit jjtn000 = new ASTDeclaratorNonInit(JJTDECLARATORNONINIT);
                             boolean jjtc000 = true;
                             jjtree.openNodeScope(jjtn000);Token t;
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case RESB:
        t = jj_consume_token(RESB);
        break;
      case RESW:
        t = jj_consume_token(RESW);
        break;
      default:
        jj_la1[24] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
            jjtree.closeNodeScope(jjtn000, true);
            jjtc000 = false;
            jjtn000.value = t.image.toUpperCase();
    } finally {
            if (jjtc000) {
              jjtree.closeNodeScope(jjtn000, true);
            }
    }
  }

  final public void Values() throws ParseException {
                 /*@bgen(jjtree) Values */
  ASTValues jjtn000 = new ASTValues(JJTVALUES);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      Value();
      label_11:
      while (true) {
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case 59:
          ;
          break;
        default:
          jj_la1[25] = jj_gen;
          break label_11;
        }
        jj_consume_token(59);
        Value();
      }
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Value() throws ParseException {
    switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
    case INTEGER_LITERAL:
      Integer();
      break;
    case CHAR_LITERAL:
      Char();
      break;
    case STR_LITERAL:
      Str();
      break;
    default:
      jj_la1[26] = jj_gen;
      jj_consume_token(-1);
      throw new ParseException();
    }
  }

  final public void Label() throws ParseException {
                /*@bgen(jjtree) Label */
                 ASTLabel jjtn000 = new ASTLabel(JJTLABEL);
                 boolean jjtc000 = true;
                 jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(IDENTIFIER);
      jj_consume_token(60);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image;
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Id() throws ParseException {
             /*@bgen(jjtree) Id */
              ASTId jjtn000 = new ASTId(JJTID);
              boolean jjtc000 = true;
              jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(IDENTIFIER);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image;
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Integer() throws ParseException {
                  /*@bgen(jjtree) Integer */
  ASTInteger jjtn000 = new ASTInteger(JJTINTEGER);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      jjtn000.value = jj_consume_token(INTEGER_LITERAL).image;
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Char() throws ParseException {
               /*@bgen(jjtree) Char */
                ASTChar jjtn000 = new ASTChar(JJTCHAR);
                boolean jjtc000 = true;
                jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(CHAR_LITERAL);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image;
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void Str() throws ParseException {
              /*@bgen(jjtree) Str */
               ASTStr jjtn000 = new ASTStr(JJTSTR);
               boolean jjtc000 = true;
               jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(STR_LITERAL);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image.substring(1, t.image.length()-1);
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void RegInt() throws ParseException {
                 /*@bgen(jjtree) RegInt */
                  ASTRegInt jjtn000 = new ASTRegInt(JJTREGINT);
                  boolean jjtc000 = true;
                  jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(REG_INT);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image.toUpperCase();
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void RegFloat() throws ParseException {
                   /*@bgen(jjtree) RegFloat */
                    ASTRegFloat jjtn000 = new ASTRegFloat(JJTREGFLOAT);
                    boolean jjtc000 = true;
                    jjtree.openNodeScope(jjtn000);Token t;
    try {
      t = jj_consume_token(REG_FLOAT);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image.toUpperCase();
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void MemRef() throws ParseException {
                 /*@bgen(jjtree) MemRef */
  ASTMemRef jjtn000 = new ASTMemRef(JJTMEMREF);
  boolean jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
    try {
      jj_consume_token(61);
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case REG_INT:
      case 62:
        switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
        case REG_INT:
          RegInt();
          break;
        case 62:
          jj_consume_token(62);
          RegInt();
          switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
          case 64:
          case 65:
            MemOffset();
            break;
          default:
            jj_la1[27] = jj_gen;
            ;
          }
          jj_consume_token(63);
          break;
        default:
          jj_la1[28] = jj_gen;
          jj_consume_token(-1);
          throw new ParseException();
        }
        break;
      case IDENTIFIER:
        Id();
        break;
      default:
        jj_la1[29] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case 60:
        MemSize();
        break;
      default:
        jj_la1[30] = jj_gen;
        ;
      }
    } catch (Throwable jjte000) {
    if (jjtc000) {
      jjtree.clearNodeScope(jjtn000);
      jjtc000 = false;
    } else {
      jjtree.popNode();
    }
    if (jjte000 instanceof RuntimeException) {
      {if (true) throw (RuntimeException)jjte000;}
    }
    if (jjte000 instanceof ParseException) {
      {if (true) throw (ParseException)jjte000;}
    }
    {if (true) throw (Error)jjte000;}
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void MemOffset() throws ParseException {
                    /*@bgen(jjtree) MemOffset */
                     ASTMemOffset jjtn000 = new ASTMemOffset(JJTMEMOFFSET);
                     boolean jjtc000 = true;
                     jjtree.openNodeScope(jjtn000);Token t1, t2;
    try {
      switch ((jj_ntk==-1)?jj_ntk():jj_ntk) {
      case 64:
        t1 = jj_consume_token(64);
        break;
      case 65:
        t1 = jj_consume_token(65);
        break;
      default:
        jj_la1[31] = jj_gen;
        jj_consume_token(-1);
        throw new ParseException();
      }
      t2 = jj_consume_token(INTEGER_LITERAL);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t1.image.equals("-") ? t1.image + t2.image : t2.image;
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  final public void MemSize() throws ParseException {
                  /*@bgen(jjtree) MemSize */
                   ASTMemSize jjtn000 = new ASTMemSize(JJTMEMSIZE);
                   boolean jjtc000 = true;
                   jjtree.openNodeScope(jjtn000);Token t;
    try {
      jj_consume_token(60);
      t = jj_consume_token(BYTE);
    jjtree.closeNodeScope(jjtn000, true);
    jjtc000 = false;
    jjtn000.value = t.image.toUpperCase();
    } finally {
    if (jjtc000) {
      jjtree.closeNodeScope(jjtn000, true);
    }
    }
  }

  /** Generated Token Manager. */
  public M2AsmParserTokenManager token_source;
  SimpleCharStream jj_input_stream;
  /** Current token. */
  public Token token;
  /** Next token. */
  public Token jj_nt;
  private int jj_ntk;
  private int jj_gen;
  final private int[] jj_la1 = new int[32];
  static private int[] jj_la1_0;
  static private int[] jj_la1_1;
  static private int[] jj_la1_2;
  static {
      jj_la1_init_0();
      jj_la1_init_1();
      jj_la1_init_2();
   }
   private static void jj_la1_init_0() {
      jj_la1_0 = new int[] {0x200,0x0,0x0,0x200,0x0,0x0,0x0,0x200,0x200,0x200,0x200,0x201,0xfffffc00,0x200,0x0,0xfffffc00,0x200,0x201,0x0,0x88,0x0,0xfffffc00,0x88,0x0,0x0,0x0,0x188,0x0,0x0,0x0,0x0,0x0,};
   }
   private static void jj_la1_init_1() {
      jj_la1_1 = new int[] {0x0,0x7000,0x7000,0x0,0x600,0x800,0x600,0x0,0x0,0x0,0x0,0x0,0x8f11ff,0x0,0x800000,0xf11ff,0x0,0x0,0x8000000,0x20e00000,0xf0000,0x1ff,0x20e00000,0x30000,0xc0000,0x8000000,0x0,0x0,0x40200000,0x40a00000,0x10000000,0x0,};
   }
   private static void jj_la1_init_2() {
      jj_la1_2 = new int[] {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x3,};
   }

  /** Constructor with InputStream. */
  public M2AsmParser(java.io.InputStream stream) {
     this(stream, null);
  }
  /** Constructor with InputStream and supplied encoding */
  public M2AsmParser(java.io.InputStream stream, String encoding) {
    try { jj_input_stream = new SimpleCharStream(stream, encoding, 1, 1); } catch(java.io.UnsupportedEncodingException e) { throw new RuntimeException(e); }
    token_source = new M2AsmParserTokenManager(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  /** Reinitialise. */
  public void ReInit(java.io.InputStream stream) {
     ReInit(stream, null);
  }
  /** Reinitialise. */
  public void ReInit(java.io.InputStream stream, String encoding) {
    try { jj_input_stream.ReInit(stream, encoding, 1, 1); } catch(java.io.UnsupportedEncodingException e) { throw new RuntimeException(e); }
    token_source.ReInit(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jjtree.reset();
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  /** Constructor. */
  public M2AsmParser(java.io.Reader stream) {
    jj_input_stream = new SimpleCharStream(stream, 1, 1);
    token_source = new M2AsmParserTokenManager(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  /** Reinitialise. */
  public void ReInit(java.io.Reader stream) {
    jj_input_stream.ReInit(stream, 1, 1);
    token_source.ReInit(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jjtree.reset();
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  /** Constructor with generated Token Manager. */
  public M2AsmParser(M2AsmParserTokenManager tm) {
    token_source = tm;
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  /** Reinitialise. */
  public void ReInit(M2AsmParserTokenManager tm) {
    token_source = tm;
    token = new Token();
    jj_ntk = -1;
    jjtree.reset();
    jj_gen = 0;
    for (int i = 0; i < 32; i++) jj_la1[i] = -1;
  }

  private Token jj_consume_token(int kind) throws ParseException {
    Token oldToken;
    if ((oldToken = token).next != null) token = token.next;
    else token = token.next = token_source.getNextToken();
    jj_ntk = -1;
    if (token.kind == kind) {
      jj_gen++;
      return token;
    }
    token = oldToken;
    jj_kind = kind;
    throw generateParseException();
  }


/** Get the next Token. */
  final public Token getNextToken() {
    if (token.next != null) token = token.next;
    else token = token.next = token_source.getNextToken();
    jj_ntk = -1;
    jj_gen++;
    return token;
  }

/** Get the specific Token. */
  final public Token getToken(int index) {
    Token t = token;
    for (int i = 0; i < index; i++) {
      if (t.next != null) t = t.next;
      else t = t.next = token_source.getNextToken();
    }
    return t;
  }

  private int jj_ntk() {
    if ((jj_nt=token.next) == null)
      return (jj_ntk = (token.next=token_source.getNextToken()).kind);
    else
      return (jj_ntk = jj_nt.kind);
  }

  private java.util.List<int[]> jj_expentries = new java.util.ArrayList<int[]>();
  private int[] jj_expentry;
  private int jj_kind = -1;

  /** Generate ParseException. */
  public ParseException generateParseException() {
    jj_expentries.clear();
    boolean[] la1tokens = new boolean[66];
    if (jj_kind >= 0) {
      la1tokens[jj_kind] = true;
      jj_kind = -1;
    }
    for (int i = 0; i < 32; i++) {
      if (jj_la1[i] == jj_gen) {
        for (int j = 0; j < 32; j++) {
          if ((jj_la1_0[i] & (1<<j)) != 0) {
            la1tokens[j] = true;
          }
          if ((jj_la1_1[i] & (1<<j)) != 0) {
            la1tokens[32+j] = true;
          }
          if ((jj_la1_2[i] & (1<<j)) != 0) {
            la1tokens[64+j] = true;
          }
        }
      }
    }
    for (int i = 0; i < 66; i++) {
      if (la1tokens[i]) {
        jj_expentry = new int[1];
        jj_expentry[0] = i;
        jj_expentries.add(jj_expentry);
      }
    }
    int[][] exptokseq = new int[jj_expentries.size()][];
    for (int i = 0; i < jj_expentries.size(); i++) {
      exptokseq[i] = jj_expentries.get(i);
    }
    return new ParseException(token, exptokseq, tokenImage);
  }

  /** Enable tracing. */
  final public void enable_tracing() {
  }

  /** Disable tracing. */
  final public void disable_tracing() {
  }

                          }
