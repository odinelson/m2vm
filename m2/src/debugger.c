/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "exec.h"
#include "opcodes.h"
#include "utils.h"

/*maximo de caracteres no buffer para leitura de comandos do debugger*/
#define MAX_DBG_CMD  50
#define BAD_DBG_CMD  do { fprintf(stderr, "Debugger: Bad command: \"%s\"\n", dbgCmd); fflush(stderr); } while(0)

char dbgCmd[MAX_DBG_CMD+1];

void readDebuggerCmd() {
  int sz;
  putchar(10);
  while (1) {
    readStrPrompt("dbg> ", dbgCmd, MAX_DBG_CMD);
    sz = strlen(dbgCmd);
/*    if (sz >= MAX_DBG_CMD)
      fprintf(stderr, "Debugger: command too long\n");*/
    switch (dbgCmd[0]) {
      case 'q': case 'Q': {  /*quit debug mode*/
        if (dbgCmd[1] == 0) {
          MODE = STATUS_NORMAL;
          printf("Debugger: Exiting debug mode\n");
          return;
        } else BAD_DBG_CMD;
      } break;
      case 'x': case 'X': {  /*forced exit*/
        if (dbgCmd[1] == 0) {
          printf("Debugger: Aborting program\n");
          exit(-3);
        } else BAD_DBG_CMD;
      } break;
      case 'r': case 'R': {
        if (dbgCmd[1] == 0) {
          showIntRegisters();
        } else BAD_DBG_CMD;
      } break;
      case 'f': case 'F': {
        if (dbgCmd[1] == 0) {
          showFloatRegisters();
        } else BAD_DBG_CMD;
      } break;
      case 'n': case 'N': {  /*next instruction*/
        if (dbgCmd[1] == 0) {
          return;  /*give control back to VM interpreter (execM2())*/
        } else BAD_DBG_CMD;
      } break;
      case 'd': case 'D': {  /*show disassembly: TODO: specify start/end address*/
        if (dbgCmd[1] == 0) {
          int i = 0;
          Byte buffer[WORD_SIZE];
          for (; i < DT; i += WORD_SIZE) {  /*data start is code end...*/
            memcpy(buffer, ram+i, WORD_SIZE);
            printDebuggerInstr(i, buffer);
          }
        } else BAD_DBG_CMD;
      } break;
      case 'm': case 'M': {  /*dump mem*/
        char dummy='\0';
        int start=-1, end=-1;
        sscanf(dbgCmd, "%c %x %x", &dummy, &start, &end);  /*parameters given in hex!*/
        if (dummy != '\0' && start != -1 && end != -1) {
          printf("RAM Dump (from %08X to %08X):\n", start, end);
          dumpRAM(start, end, 0);
        } else BAD_DBG_CMD;

      } break;
      case 's': case 'S': {  /*dump stack*/
        if (dbgCmd[1] == 0) {
          printf("Stack Dump\n");
          dumpRAM(SP, SB, 1);
        } else BAD_DBG_CMD;
      } break;
      default: BAD_DBG_CMD;
    }
  }
}

/*
  Prints a instruction, disassembled.
  Returns location of next instruction.
*/

int printDebuggerInstr(int loc, Byte* instrBuffer) {
  switch (instrBuffer[0]) {
    /*0 arg:*/
    case NOP: case HALT: case RET: PRINT_0ARG(loc, instrBuffer); break;
    /*1 arg, imm:*/
    case INT: PRINT_1ARG(loc, instrBuffer); break;
    case JMP: case CALL:
    case JE: case JNE:
    case JL: case JLE:
    case JG: case JGE: PRINT_JUMP(loc, instrBuffer); break;
    /*1 arg, int reg:*/
    case INC: case DEC:
    case NEG: case NOT:
    case PUSH: case POP: PRINT_1ARG_R(loc, instrBuffer);  break;
    /*1 arg, float reg:*/
    case NEGF:
    case PUSHF: case POPF: PRINT_1ARG_F(loc, instrBuffer);  break;
    /*2 args, integer register and imm:*/
    case ADDI:
    case ANDI: case ORI:
    case XORI: case CMPI:
    case SHR: case SHL:	PRINT_2ARGS_RI(loc, instrBuffer);  break;
    /*2 args, integer registers:*/
    case ADD: case SUB:
    case MUL: case DIV:
    case AND: case OR:
    case XOR: case CPY: case CMP: PRINT_2ARGS_RR(loc, instrBuffer);  break;
    /*2 args, float registers:*/
    case ADDF: case SUBF:
    case MULF: case DIVF:
    case CPYF: case CMPF: PRINT_2ARGS_FF(loc, instrBuffer); break;
    /*2 args, mixed registers:*/
    case CPYFR: PRINT_CPYFR(loc, instrBuffer); break;
    case CPYRF: PRINT_CPYRF(loc, instrBuffer); break;
    /*2 args, load to int register from immediate*/
    case LODI:  PRINT_LOD_RI(loc, instrBuffer); break;
    /*2 args, load to int register from *(register+byte_offset)*/
    case LOD: case LODB: PRINT_LOD_RX(loc, instrBuffer,1); break; /*1 = positive sign for offset*/
    /*special case, load to float register*/
    case LODFI: PRINT_LODFI(loc, instrBuffer); break;
    /*special case, load to float register from *(register+byte_offset)*/
    case LODF: PRINT_LOD_FX(loc, instrBuffer,1); break; /*1 = positive sign for offset*/
    /*2 args, stor to mem (specified as *(register+byte_offset)) from int register*/
    case STOR: case STORB: PRINT_STOR_XR(loc, instrBuffer,1); break; /*1 = positive sign for offset*/
    /*special case, stor to mem (specified as *(register+byte_offset)) from float register*/
    case STORF: PRINT_STOR_XF(loc, instrBuffer,1); break; /*1 = positive sign for offset*/
    /*any other (probably undefined or mis-assembled): just print the byte.*/
    default: printf("\nIP = [%08X] %02X\n", loc, ram[loc]); break;
  }
  return 0;
}
