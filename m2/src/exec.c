/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "opcodes.h"
#include "debugger.h"
#include "exec.h"
#include "exec_interrupt.h"
#include "exec_internal.h"
#include "m2jit.h"

Int32 reg_i[16];
Real32 reg_f[16];
JitBuffer* code;

static void showBanner() {  /*if running in debug mode...*/
  printf("\nM2 Virtual Machine version %d.%d\nby Odilon Nelson <odilon.nelson@gmail.com>\n", M2_VERSION_MAJOR, M2_VERSION_MINOR);
}

void execM2() {
  Byte instrBuffer[WORD_SIZE];  /*holds current instruction to decode*/
  Byte r1, r2;  /*registers referenced by instruction*/
  int finished = 0;
  IP = 0;       /*Instruction Pointer*/
  code = allocBuffer(4096);

  if (MODE == STATUS_DEBUG)
    showBanner();

  /*main loop
    Obs: 32-bit instruction format, with a single decoding pass:
    xxxxxxxx xxxx xxxx xxxxxxxx xxxxxxxx
    op       rr        imm or offset*/
  while (!finished) {
    if (MODE == STATUS_DEBUG)
      readDebuggerCmd();

    /*fetches instruction from RAM*/
    memcpy(instrBuffer, ram+IP, WORD_SIZE);

    if (MODE == STATUS_DEBUG) {
      putchar('\n'); printDebuggerInstr(IP, instrBuffer);
    }
    /*instruction decoding+executing*/
    switch (instrBuffer[0]) {  /*opcode*/
      case NOP: HANDLE_NOP break;
      case HALT: HANDLE_HALT break;
      case INC: HANDLE_INC break;
      case DEC: HANDLE_DEC break;
      case ADD: genADD_2REG(code, reg_i[r1],reg_i[r2]);
				reg_i[r1] = execBuffer(code);
				break;
      case ADDI: HANDLE_ADDI break;
      case SUB: HANDLE_SUB break;
      case MUL: HANDLE_MUL break;
      case DIV: HANDLE_DIV break;
      case NEG: HANDLE_NEG break;
      case ADDF: HANDLE_ADDF break;
      case SUBF: HANDLE_SUBF break;
      case MULF: HANDLE_MULF break;
      case DIVF: HANDLE_DIVF break;
      case NEGF: HANDLE_NEGF break;
      case AND: HANDLE_AND break;
      case ANDI: HANDLE_ANDI break;
      case OR: HANDLE_OR break;
      case ORI: HANDLE_ORI break;
      case XOR: HANDLE_XOR break;
      case XORI: HANDLE_XORI break;
      case NOT: HANDLE_NOT break;
      case SHL: HANDLE_SHL break;
      case SHR: HANDLE_SHR break;
      case CPY: HANDLE_CPY break;
      case CPYF: HANDLE_CPYF break;
      case CPYFR: HANDLE_CPYFR break;
      case CPYRF: HANDLE_CPYRF break;
      case CMP: HANDLE_CMP break;
      case CMPI: HANDLE_CMPI break;
      case CMPF: HANDLE_CMPF break;
      case LOD: HANDLE_LOD break;
      case LODB: HANDLE_LODB break;
      case LODF: HANDLE_LODF break;
      case LODI: HANDLE_LODI break;
      case LODFI: HANDLE_LODFI break;
      case STOR: HANDLE_STOR break;
      case STORB: HANDLE_STORB break;
      case STORF: HANDLE_STORF break;
      case JMP: HANDLE_JMP break;
      case JE: HANDLE_JE break;
      case JNE: HANDLE_JNE break;
      case JL: HANDLE_JL break;
      case JLE: HANDLE_JLE break;
      case JG: HANDLE_JG break;
      case JGE: HANDLE_JGE break;
      case INT: HANDLE_INT break;
      case CALL: HANDLE_CALL break;
      case RET: HANDLE_RET break;
      case PUSH: HANDLE_PUSH break;
      case POP: HANDLE_POP break;
      case PUSHF: HANDLE_PUSHF break;
      case POPF: HANDLE_POPF break;
      default: HANDLE_INVALID break;
    }
    /*Note that all instructions are the same size, so we can increment IP here*/
    IP += WORD_SIZE;
    DBG("finished=%d", finished);
  }

  if (MODE == STATUS_DEBUG && finished)  /*last chance to debug before HALT*/
      readDebuggerCmd();
}

void illegalOp(int ip) {
  fprintf(stderr, "** Program closed: illegal operation at [%08X].\n", ip);
  fflush(stderr);
  exit(-1);
}
