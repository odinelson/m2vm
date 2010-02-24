/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#ifndef OPCODES_H
#define OPCODES_H

typedef enum OPCODE {
  NOP = 0x0,   /*0 arg; No Operation*/
  HALT = 0x1,   /*0 arg; Halt VM*/
  INC = 0x2,   /*1 arg; Increment value in Integer Register*/
  DEC = 0x3,   /*1 arg; Decrement value in Integer Register*/
  ADD = 0x4,   /*2 arg; Add values in Integer Registers*/
  ADDI = 0x5,   /*2 arg; Add imm to Integer Register*/
  SUB = 0x6,   /*2 arg; Subtract values in Integer Registers*/
  MUL = 0x7,   /*2 arg; Multiply values in Integer Registers*/
  DIV = 0x8,   /*2 arg; Divide values in Integer Registers*/
  NEG = 0x9,   /*1 arg; Negate value in Integer Register*/
  ADDF = 0xa,   /*2 arg; Add values in Floating-point Registers*/
  SUBF = 0xb,   /*2 arg; Subtract values in Floating-point Registers*/
  MULF = 0xc,   /*2 arg; Multiply values in Floating-point Registers*/
  DIVF = 0xd,   /*2 arg; Divide values in Floating-point Registers*/
  NEGF = 0xe,   /*1 arg; Negate value in Floating-point Register*/
  AND = 0xf,   /*2 arg; Logical AND values in Integer Registers*/
  ANDI = 0x10,   /*2 arg; Logical AND Integer Register & imm*/
  OR = 0x11,   /*2 arg; Logical OR values in Integer Registers*/
  ORI = 0x12,   /*2 arg; Logical OR Integer Register & imm*/
  XOR = 0x13,   /*2 arg; Logical XOR values in Integer Registers*/
  XORI = 0x14,   /*2 arg; Logical XOR Integer Register & imm*/
  NOT = 0x15,   /*1 arg; Logical NOT value in Integer Register*/
  SHL = 0x16,   /*2 arg; Left-shift by imm bytes value in Integer Register*/
  SHR = 0x17,   /*2 arg; Right-shift by imm bytes value in Integer Register*/
  CPY = 0x18,   /*2 arg; Copy value between Integer Registers*/
  CPYF = 0x19,   /*2 arg; Copy value between Floating-point Registers*/
  CPYFR = 0x1a,   /*2 arg; Copy value from Integer Register to Floating-point Register*/
  CPYRF = 0x1b,   /*2 arg; Copy value from Floating-point Register to Integer Register*/
  CMP = 0x1c,   /*2 arg; Compare values in Integer Registers; store result in FLAGS*/
  CMPI = 0x1d,   /*2 arg; Compare value in Integer Register & imm; store result in FLAGS*/
  CMPF = 0x1e,   /*2 arg; Compare values in Float Registers; store result in FLAGS*/
  LOD = 0x1f,   /*2 arg; Load word to Integer Register1 from RAM, indexed (address given by Register2+offset)*/
  LODB = 0x20,   /*2 arg; Load byte to Integer Register1 from RAM, indexed (address given by Register2+offset)*/
  LODF = 0x21,   /*2 arg; Load value to Floating-point Register1 from RAM, indexed (address given by Int Register2+offset)*/
  LODI = 0x22,   /*2 arg; Load halfword immediate (sign-extended) to Integer Register*/
  LODFI = 0x23,   /*2 arg; Load halfword immediate (sign-extended) to Floating-point Register*/
  STOR = 0x24,   /*2 arg; Store word in Integer Register2 to RAM, indexed (address given by Register1+offset)*/
  STORB = 0x25,   /*2 arg; Store byte in Integer Register2 to RAM, indexed (address given by Register1+offset)*/
  STORF = 0x26,   /*2 arg; Store value (dword-sized) in Floating-point Register2 to RAM, indexed (address given by Register1+offset)*/
  JMP = 0x27,   /*1 arg; Jump to address (IP relative)*/
  JE = 0x28,   /*1 arg; Jump to address (IP relative) if values in last comparison are Equal*/
  JNE = 0x29,   /*1 arg; Jump to address (IP relative) if values in last comparison are Not Equal*/
  JL = 0x2a,   /*1 arg; Jump to address (IP relative) if 1st value is Less than 2nd value in last comparison*/
  JLE = 0x2b,   /*1 arg; Jump to address (IP relative) if 1st value is Less than or Equal to 2nd value in last comparison*/
  JG = 0x2c,   /*1 arg; Jump to address (IP relative) if 1st value is Greater than 2nd value in last comparison*/
  JGE = 0x2d,   /*1 arg; Jump to address (IP relative) if 1st value is Greater than or Equal to 2nd value in last comparison*/
  INT = 0x2e,   /*1 arg; Execute Interrupt. (Interrupt number is given in immediate arg - function is in IR)*/
  CALL = 0x2f,   /*1 arg; Call procedure at address (IP relative)*/
  RET = 0x30,   /*0 arg; Return from procedure*/
  PUSH = 0x31,   /*1 arg; Push dword value in Integer Register to stack segment*/
  POP = 0x32,   /*1 arg; Pop dword value in stack segment to Integer Register*/
  PUSHF = 0x33,   /*1 arg; Push value in Floating-point Register to stack segment*/
  POPF = 0x34,   /*1 arg; Pop value in stack segment to Floating-point Register*/
  LAST_OPCODE = POPF
} OpCode;

extern char* OPCODE_STR[];

#endif /*OPCODES_H*/
