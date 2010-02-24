/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

/* Macros for executing instructions... these are not functions, for better performance */

#ifndef EXEC_INTERNAL_H
#define EXEC_INTERNAL_H

#define HANDLE_NOP   { ; }

#define HANDLE_HALT  { finished = 1; }

#define _HANDLE_OP_1REG_INT(statement)  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          statement; \
        }

#define HANDLE_INC  _HANDLE_OP_1REG_INT(reg_i[r1]++)
#define HANDLE_DEC  _HANDLE_OP_1REG_INT(reg_i[r1]--)

#define _HANDLE_OP_2REGS_INT(statement)  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          statement; \
        }

#define HANDLE_ADD  _HANDLE_OP_2REGS_INT(reg_i[r1] += reg_i[r2])

#define HANDLE_ADDI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] += (int)bytesToInt16(&instrBuffer[2]); \
        }


#define HANDLE_SUB  _HANDLE_OP_2REGS_INT(reg_i[r1] -= reg_i[r2])
#define HANDLE_MUL  _HANDLE_OP_2REGS_INT(reg_i[r1] *= reg_i[r2])

#define HANDLE_DIV  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          CHECK_INVALID_REG_DESTINATION(r2); \
          int v1 = reg_i[r1], v2 = reg_i[r2]; \
          reg_i[r1] = v1 / v2; \
          reg_i[r2] = v1 % v2; \
        }

#define HANDLE_NEG  _HANDLE_OP_1REG_INT(reg_i[r1] = -reg_i[r1])

#define _HANDLE_OP_2REGS_FLOAT(statement)  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGSF(r1, r2); \
          statement; \
        }

#define HANDLE_ADDF  _HANDLE_OP_2REGS_FLOAT(reg_f[r1] += reg_f[r2])
#define HANDLE_SUBF  _HANDLE_OP_2REGS_FLOAT(reg_f[r1] -= reg_f[r2])
#define HANDLE_MULF  _HANDLE_OP_2REGS_FLOAT(reg_f[r1] *= reg_f[r2])
#define HANDLE_DIVF  _HANDLE_OP_2REGS_FLOAT(reg_f[r1] /= reg_f[r2])

#define HANDLE_NEGF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          reg_f[r1] = -reg_f[r1]; \
        }

#define HANDLE_AND  _HANDLE_OP_2REGS_INT(reg_i[r1] &= reg_i[r2])

#define HANDLE_ANDI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] &= (int)bytesToInt16(&instrBuffer[2]); \
        }

#define HANDLE_OR  _HANDLE_OP_2REGS_INT(reg_i[r1] |= reg_i[r2])

#define HANDLE_ORI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] |= (int)bytesToInt16(&instrBuffer[2]); \
        }

#define HANDLE_XOR  _HANDLE_OP_2REGS_INT(reg_i[r1] ^= reg_i[r2])

#define HANDLE_XORI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] ^= (int)bytesToInt16(&instrBuffer[2]); \
        }

#define HANDLE_NOT  _HANDLE_OP_1REG_INT(reg_i[r1] = !reg_i[r1])

#define HANDLE_SHL  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] = reg_i[r1] << (int)bytesToInt16(&instrBuffer[2]); \
        }

#define HANDLE_SHR  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] = reg_i[r1] >> (int)bytesToInt16(&instrBuffer[2]); \
        }

#define HANDLE_CPY  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] = reg_i[r2]; \
          DBG("CPY: R%d=%d; R%d=%d", r1, reg_i[r1], r2, reg_i[r2]); \
        }

#define HANDLE_CPYF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGSF(r1, r2); \
          reg_f[r1] = reg_f[r2]; \
          DBG("CPY: F%d=%f; F%d=%f", r1, reg_f[r1], r2, reg_f[r2]); \
        }

#define HANDLE_CPYFR  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          reg_f[r1] = (float)reg_i[r2]; \
          DBG("CPY: F%d=%f; R%d=%d", r1, reg_f[r1], r2, reg_i[r2]); \
        }

#define HANDLE_CPYRF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          CHECK_INVALID_REGF(r2); \
          reg_i[r1] = (int)reg_f[r2]; \
          DBG("CPY: R%d=%d; F%d=%f", r1, reg_i[r1], r2, reg_f[r2]); \
        }

#define HANDLE_CMP  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          FLAGS = 0; \
          if (reg_i[r1] == reg_i[r2]) { FLAGS |= FLAG_EQ; } \
          if (reg_i[r1] < reg_i[r2]) { FLAGS |= FLAG_LT; } \
          if (reg_i[r1] > reg_i[r2]) { FLAGS |= FLAG_GT; } \
          DBG("CMP: R%d=%d; R%d=%d  ;  FLAGS=%d", r1, reg_i[r1], r2, reg_i[r2], FLAGS); \
        }

#define HANDLE_CMPI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          Int16 i = bytesToInt16(&instrBuffer[2]); \
          FLAGS = 0; \
          if (reg_i[r1] == i) { FLAGS |= FLAG_EQ; } \
          if (reg_i[r1] < i) { FLAGS |= FLAG_LT; } \
          if (reg_i[r1] > i) { FLAGS |= FLAG_GT; } \
          DBG("CMP: R%d=%d; %d  ;  FLAGS=%d", r1, reg_i[r1], i, FLAGS); \
        }

#define HANDLE_CMPF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGSF(r1, r2); \
          FLAGS = 0; \
          if (reg_f[r1] == reg_f[r2]) { FLAGS |= FLAG_EQ; } \
          if (reg_f[r1] < reg_f[r2]) { FLAGS |= FLAG_LT; } \
          if (reg_f[r1] > reg_f[r2]) { FLAGS |= FLAG_GT; } \
          DBG("CMP: F%d=%f; F%d=%f  ;  FLAGS=%d", r1, reg_f[r1], r2, reg_f[r2], FLAGS); \
        }

/*Indexed LOD R,*(R+signed_offset)*/
#define HANDLE_LOD  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          reg_i[r1] = bytesToInt32(&ram[reg_i[r2]+offset]); \
          DBG("LOD : R%d=%d; R%d=%d; offset=%d", r1, reg_i[r1], r2, reg_i[r2], offset); \
        }

#define HANDLE_LODB  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          reg_i[r1] = (int)ram[reg_i[r2]+offset]; \
          DBG("LODB : R%d=%d; R%d=%d; offset=%d", r1, reg_i[r1], r2, reg_i[r2], offset); \
        }

#define HANDLE_LODF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          reg_f[r1] = bytesToFloat(&ram[reg_i[r2]+offset]); \
          DBG("LODF : F%d=%f; R%d=%d; offset=%d", r1, reg_f[r1], r2, reg_i[r2], offset); \
        }

/*LOD immediate*/
#define HANDLE_LODI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] = (int)bytesToInt16(&instrBuffer[2]); \
          DBG("R%d=%d", r1, reg_i[r1]); \
        }

#define HANDLE_LODFI  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          reg_f[r1] = (float)bytesToInt16(&instrBuffer[2]); \
          DBG("F%d=%f", r1, reg_f[r1]); \
        }

/*Indexed STOR *(R+offset),R*/
#define HANDLE_STOR  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          int32ToBytes(reg_i[r2], &ram[reg_i[r1]+offset]); \
          DBG("STOR : R%d=%d; offset=%d; R%d=%d", r1, reg_i[r1], offset, r2, reg_i[r2]); \
        }

#define HANDLE_STORB  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          ram[reg_i[r1]+offset] = (Byte)reg_i[r2]; \
          DBG("STORB : R%d=%d; offset=%d; R%d=%d", r1, reg_i[r1], offset, r2, reg_i[r2]); \
        }

#define HANDLE_STORF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          r2 = LO_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r2); \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          floatToBytes(reg_f[r2], &ram[reg_i[r1]+offset]); \
          DBG("STORF : F%d=%f; offset=%d; R%d=%d", r1, reg_f[r1], offset, r2, reg_i[r2]); \
        }

/*goto addr (relative)
  offset relative to next instruction address
  (because IP has already been incremented by the fetch)*/
#define HANDLE_JMP  {\
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          DBG("JMP to %d", IP+(int)offset); \
          IP += (int)offset; \
        }

/*conditional jumps*/

#define _HANDLE_CONDITIONAL_JUMP(cond, descr)  {\
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          if (cond) { \
            DBG("%s to %d", descr, IP+(int)offset); \
            IP += (int)offset; \
          } \
        }

#define HANDLE_JE    _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_EQ, "JE")
#define HANDLE_JNE   _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_LT || FLAGS == FLAG_GT, "JNE")
#define HANDLE_JL    _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_LT, "JL")
#define HANDLE_JLE   _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_LT || FLAGS == FLAG_EQ, "JLE")
#define HANDLE_JG    _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_GT, "JG")
#define HANDLE_JGE   _HANDLE_CONDITIONAL_JUMP(FLAGS == FLAG_GT || FLAGS == FLAG_EQ, "JGE")


/*Interrupt: immediate contains interrupt number and IR contains function number on low halfword
  TODO: error code mechanism?*/
#define HANDLE_INT  {\
          Int16 int_num = bytesToInt16(&instrBuffer[2]); \
          Int16 func_num = LO_HALFWORD(IR); \
          DBG("Interrupt %d, function %d", int_num, func_num); \
          execInterrupt(int_num, func_num); \
        }

#define HANDLE_CALL  {\
          /*pushes return address (after CALL)*/ \
          SP -= WORD_SIZE; \
          CHECK_STACK_OVERFLOW \
          int32ToBytes(IP, &ram[SP]); \
          /*goto relative address*/ \
          Int16 offset = bytesToInt16(&instrBuffer[2]); \
          DBG("CALL: current addr=%d; goto %d; retAddr=%d", IP-WORD_SIZE, IP+offset, IP); \
          IP += (int)offset; \
        }

#define HANDLE_RET  {\
          /*pops return address in IP*/ \
          IP = bytesToInt32(&ram[SP]); \
          SP += WORD_SIZE; \
          CHECK_STACK_UNDERFLOW \
          DBG("RET: returning at %d", IP); \
        }

#define HANDLE_PUSH  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          SP -= WORD_SIZE; \
          CHECK_STACK_OVERFLOW \
          int32ToBytes(reg_i[r1], &ram[SP]); \
          DBG("PUSH: Pushing R%d with value %d", r1, reg_i[r1]); \
          DBG("PUSH: SP is now %d; Value at *SP = %d", SP, bytesToInt32(&ram[SP])); \
        }

#define HANDLE_POP  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REG_DESTINATION(r1); \
          reg_i[r1] = bytesToInt32(&ram[SP]); \
          SP += WORD_SIZE; \
          CHECK_STACK_UNDERFLOW \
          DBG("SP is now %d; Value at *SP = %d; value at R%d = %d", SP, bytesToInt32(&ram[SP]), r1, reg_i[r1]); \
        }

#define HANDLE_PUSHF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          SP -= WORD_SIZE; \
          CHECK_STACK_OVERFLOW \
          floatToBytes(reg_f[r1], &ram[SP]); \
          DBG("SP is now %d; Value at *SP = %f", SP, bytesToFloat(&ram[SP])); \
        }

#define HANDLE_POPF  {\
          r1 = HI_NIBBLE(instrBuffer[1]); \
          CHECK_INVALID_REGF(r1); \
          reg_f[r1] = bytesToFloat(&ram[SP]); \
          SP += WORD_SIZE; \
          CHECK_STACK_UNDERFLOW \
          DBG("SP is now %d; Value at *SP = %f; value at F%d = %f", SP, bytesToFloat(&ram[SP]), r1, reg_f[r1]); \
        }

#define HANDLE_INVALID  {\
          fprintf(stderr, "ERROR: Invalid opcode at [%08X] (%d decimal): %02X\n", (unsigned)IP, IP, ram[IP]); \
          fflush(stderr); \
          exit(-1); \
        }

#endif /*EXEC_INTERNAL_H*/

