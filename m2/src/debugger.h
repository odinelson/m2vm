/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "opcodes.h"
#include "utils.h"
#include "exec.h"

void readDebuggerCmd();
int printDebuggerInstr(int loc, Byte* instrBuffer);

#define ADDR_FMT	   "[%08X]:"

/* Macros para a maioria das instruções*/

#define PRINT_0ARG(loc, instr)      printf(ADDR_FMT " %s\n", loc, OPCODE_STR[instr[0]])
#define PRINT_1ARG(loc, instr)      printf(ADDR_FMT " %s %d\n", loc, OPCODE_STR[instr[0]], bytesToInt16(&instr[2]))
/* the only difference to PRINT_1ARG is the signed integer... */
#define PRINT_JUMP(loc, instr)      printf(ADDR_FMT " %s %+d\n", loc, OPCODE_STR[instr[0]], bytesToInt16(&instr[2]))
#define PRINT_1ARG_R(loc, instr)    printf(ADDR_FMT " %s %s\n", loc, OPCODE_STR[instr[0]], REG_NAME[HI_NIBBLE(instr[1])])
#define PRINT_1ARG_F(loc, instr)    printf(ADDR_FMT " %s F%d\n", loc, OPCODE_STR[instr[0]], HI_NIBBLE(instr[1]))
#define PRINT_2ARGS_RI(loc, instr)  printf(ADDR_FMT " %s %s, %d\n", loc, OPCODE_STR[instr[0]], REG_NAME[HI_NIBBLE(instr[1])], bytesToInt16(&instr[2]))
#define PRINT_2ARGS_RR(loc, instr)  printf(ADDR_FMT " %s %s, %s\n", loc, OPCODE_STR[instr[0]], REG_NAME[HI_NIBBLE(instr[1])], REG_NAME[LO_NIBBLE(instr[1])])
#define PRINT_2ARGS_FF(loc, instr)  printf(ADDR_FMT " %s F%d, F%d\n", loc, OPCODE_STR[instr[0]], HI_NIBBLE(instr[1]), LO_NIBBLE(instr[1]))
#define PRINT_CPYRF(loc, instr)     printf(ADDR_FMT " CPY %s, F%d\n", loc, REG_NAME[HI_NIBBLE(instr[1])], LO_NIBBLE(instr[1]))
#define PRINT_CPYFR(loc, instr)     printf(ADDR_FMT " CPY F%d, %s\n",  loc, HI_NIBBLE(instr[1]), REG_NAME[LO_NIBBLE(instr[1])])

/* Macros especializadas para LOD e STOR*/

/*util*/
#define OPERAND_SIZE(opcode)  (opcode==LODI || opcode==LOD || opcode==STOR) ? "" : ":BYTE"
/*util*/
#define IMM_VALUE(instr)  (instr[0]==LODI || instr[0]==LOD || instr[0]==STOR) ? bytesToInt16(&instr[2]) : instr[2]

#define PRINT_LOD_RI(loc, instr)       printf(ADDR_FMT " LOD %s, %d\n", loc, REG_NAME[HI_NIBBLE(instr[1])], IMM_VALUE(instr))

#define PRINT_LOD_RX(loc, instr,sign)  printf(ADDR_FMT " LOD %s, *(%s%+d)%s\n", loc, REG_NAME[HI_NIBBLE(instr[1])], REG_NAME[LO_NIBBLE(instr[1])], bytesToInt16(&instr[2]), OPERAND_SIZE(instr[0]))

/*A instrução LOD indireta com registrador Float sempre carrega 4 bytes, portanto não há necessidade de mostrar o operand Size (e mostrá-lo até confunde o usuário):*/
#define PRINT_LOD_FX(loc,instr,sign)  printf(ADDR_FMT " LOD F%d, *(%s%+d)\n", loc, HI_NIBBLE(instr[1]), REG_NAME[LO_NIBBLE(instr[1])], bytesToInt16(&instr[2]))

#define PRINT_LODFI(loc, instr)         printf(ADDR_FMT " LOD F%d, %f\n", loc, HI_NIBBLE(instr[1]), (float)bytesToInt16(&instr[2]))

#define PRINT_STOR_XR(loc, instr,sign)	printf(ADDR_FMT " STOR *(%s%+d)%s, %s\n", loc, REG_NAME[HI_NIBBLE(instr[1])], bytesToInt16(&instr[2]), OPERAND_SIZE(instr[0]), REG_NAME[LO_NIBBLE(instr[1])])

/*ver observação no LOD indireto com float...*/
#define PRINT_STOR_XF(loc, instr,sign) printf(ADDR_FMT " STOR *(%s%+d), F%d\n", loc, REG_NAME[HI_NIBBLE(instr[1])], bytesToInt16(&instr[2]), LO_NIBBLE(instr[1]))

#endif /*DEBUGGER_H*/
