/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#ifndef EXEC_H
#define EXEC_H

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif


extern Int32 reg_i[16];
extern Real32 reg_f[16];

#define WORD_SIZE  4

#define R0   reg_i[0]
#define R1   reg_i[1]
#define R2   reg_i[2]
#define R3   reg_i[3]
#define R4   reg_i[4]
#define R5   reg_i[5]
#define FR   reg_i[6]   /*flags register*/
#define IR   reg_i[7]   /*interrupt register*/
#define MR   reg_i[8]   /*mode register*/
#define DT   reg_i[9]   /*data start*/
#define UD   reg_i[10]  /*uninitialized data start*/
#define ST   reg_i[11]  /*stack top*/
#define SB   reg_i[12]  /*stack bottom*/
#define SP   reg_i[13]  /*stack pointer*/
#define FP   reg_i[14]  /*frame pointer*/
#define IP   reg_i[15]  /*instruction pointer*/

/* nomes alternativos para alguns registradores */
#define FLAGS FR
#define MODE  MR

#define F0   reg_f[0]
#define F1   reg_f[1]
#define F2   reg_f[2]
#define F3   reg_f[3]
#define F4   reg_f[4]
#define F5   reg_f[5]


#define FLAG_LT  0x01
#define FLAG_GT  0x02
#define FLAG_EQ  0x04

/*NOTA: <=, >= e <> são armazenados em combinações dos flags acima:
FLAG_LT e FLAG_GT setados significa <>, por exemplo.
O HI_BYTE(HI_HALFWORD(FLAGS)) por enquanto não é usado; pode ser usado para um flag adicional futuro*/

#define CHECK_STACK_OVERFLOW   if (SP < ST) { fprintf(stderr, "Stack Overflow!"); exit(-2); }
#define CHECK_STACK_UNDERFLOW  if (SP > SB) { fprintf(stderr, "Stack Underflow!"); exit(-2); }

#define CHECK_INVALID_REG_DESTINATION(nreg)   if ((nreg >= 9 && nreg <=12) || nreg == 15 || nreg == 6) { illegalOp(IP); }
#define CHECK_INVALID_REGF(nreg)              if (nreg > 5) { illegalOp(IP); }
#define CHECK_INVALID_REGSF(nreg1, nreg2)     if (nreg1 > 5 || nreg2 > 5) { illegalOp(IP); }

typedef enum M2STATUS {
  STATUS_NORMAL, STATUS_DEBUG
} M2Status;

void execM2();
void illegalOp(int ip);

#ifdef __cplusplus
}
#endif


#endif /*EXEC_H*/
