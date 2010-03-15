/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#include "exec.h"

/* util, from www.firstobject.com/getmillicount-milliseconds-portable-c++.htm */
int getMilliCount() {
  struct timeb tb;
  ftime(&tb);
  return tb.millitm + (tb.time & 0xfffff) * 1000;
}

/* These utilities avoid fflush(stdin), which is not portable. */

#define FLUSH_INPUT_BUFFER	while(getchar()!='\n'){}

/* The readXXX() functions below flush the output buffer to guarantee that any prompt
 * written by the program is shown before reading (this was thought primarily for Eclipse
 * console integration)
 */

Int32 readInt() {
  Int32 i;
  char buff[31];
  char* err_ptr;
  fflush(stdout);
  if (readStr(buff, 30)) {
	  i = strtol(buff, &err_ptr, 10);
	  if (buff[0] != '\n' && (*err_ptr == '\n' || *err_ptr == '\0')) {
		  FLAGS = FLAG_EQ;
		  return i;
	  } else {
		  FLAGS = FLAG_INVALID;
		  return 0;
	  }
  }
  else {
    FLAGS = FLAG_INVALID;
  	return 0;
  }
}

Real32 readFloat() {
  Real32 f;
  char buff[31];
  char* err_ptr;
  fflush(stdout);
  if (readStr(buff, 30)) {
	  f = (Real32) strtod(buff, &err_ptr);
	  if (buff[0] != '\n' && (*err_ptr == '\n' || *err_ptr == '\0')) {
		  FLAGS = FLAG_EQ;
		  return f;
	  } else {
		  FLAGS = FLAG_INVALID;
		  return 0;
	  }
  }
  else {
    FLAGS = FLAG_INVALID;
  	return 0;
  }
}

Int32 readChar() {
  fflush(stdout);
  return getchar();
}

/* Simulated interrupt routines */
void execInterrupt(Int16 int_num, Int16 func_num) {
  switch (int_num) {
    case 0: {  /*machine version*/
      R0 = (Int32)((M2_VERSION_MAJOR << 4) | M2_VERSION_MINOR);
    } break; /*case 0*/
    case 1: {  /* I/O*/
      switch (func_num) {
        case 0: putchar(R0); break;
        case 1: R0 = readChar(); break;
        case 2: printf("%d", R0); break;
        case 3: R0 = readInt(); break;
        case 4: printf("%2.4f", F0); break;
        case 5: F0 = readFloat(); break;
        case 6: printf("%s", (char*)&ram[R0]); break;
        case 7: readStr((char*)&ram[R0], -1); break; /*o tamanho do buffer (na memória da M2) não é verificado*/
        /*abre arquivo para escrita (R0: endereço de strz com nome do arquivo); retorna: ponteiro do arquivo*/
        case 8: R0 = (Int32)fopen((char*)&ram[R0], "wb"); break;
        /*abre arquivo para leitura (R0: endereço de strz com nome do arquivo); retorna: ponteiro do arquivo*/
        case 9: R0 = (Int32)fopen((char*)&ram[R0], "rb"); break;
        /*fecha arquivo (R0: handle do arquivo)*/
        case 10: fclose((FILE*)R0); break;
        /*escreve bytes no arquivo (R0: handle do arquivo, R1: numero de bytes a escrever, R2: endereço do buffer)*/
        case 11: fwrite((const void*)&ram[R2], sizeof(Byte), R1, (FILE*)R0); break;
        /*lê bytes do arquivo (R0: handle do arquivo, R1: numero de bytes a ler, R2: endereço do buffer)*/
        case 12: fread((void*)R2, sizeof(Byte), R1, (FILE*)R0); break;
        /*testa fim de arquivo (R0: handle do arquivo)*/
        case 13: R0 = (Int32)feof((FILE*)R0); break;
      }
    } break; /*case 1*/
    case 2: {  /* date/time */
      switch (func_num) {
        /* retorna timestamp UTC em segundos, desde 01/01/1970 00:00 */
        case 0: R0 = time(NULL); break;
        /* decompoe timestamp UTC (em R0) em seus componentes, em um buffer apontado por R1 (no minimo 10 bytes) */
        case 1: {
          struct tm *tm;
          time_t t = (time_t)R0;
          tm = gmtime(&t);
          ram[R1]   = (Byte)tm->tm_sec;
          ram[R1+1] = (Byte)tm->tm_min;
          ram[R1+2] = (Byte)tm->tm_hour;
          ram[R1+3] = (Byte)tm->tm_mday;
          ram[R1+4] = (Byte)(tm->tm_mon+1);
          int32ToBytes(tm->tm_year+1900, &ram[R1+5]);
          ram[R1+9] = (Byte)tm->tm_wday;
        } break;
        /* converte timestamp UTC (em R0) em data/hora local e decompoe em seus componentes, em um buffer apontado por R1 (no minimo 10 bytes) */
        case 2: {
          struct tm *tm;
          time_t t = (time_t)R0;
          tm = localtime(&t);
          ram[R1]   = (Byte)tm->tm_sec;
          ram[R1+1] = (Byte)tm->tm_min;
          ram[R1+2] = (Byte)tm->tm_hour;
          ram[R1+3] = (Byte)tm->tm_mday;
          ram[R1+4] = (Byte)(tm->tm_mon+1);
          int32ToBytes(tm->tm_year+1900, &ram[R1+5]);
          ram[R1+9] = (Byte)tm->tm_wday;
        } break;
        /* transforma uma data/hora em um buffer apontado por R0 em timestamp UTC; retorno em R0 */
        case 3: {
          struct tm tm;
          tm.tm_sec = (int)ram[R0];
          tm.tm_min = (int)ram[R0+1];
          tm.tm_hour = (int)ram[R0+2];
          tm.tm_mday = (int)ram[R0+3];
          tm.tm_mon = (int)(ram[R0+4]-1);
          tm.tm_year = bytesToInt32(&ram[R0+5])-1900;
          tm.tm_wday = (int)ram[R0+9];
          R0 = (Int32)mktime(&tm);
        } break;
        /* retorna timestamp em milissegundos */
        case 4: R0 = getMilliCount(); break;
      }
    } break; /*case 2*/
    case 3: {  /*breakpoint*/
      MODE = STATUS_DEBUG;
    } break; /*case 3*/
    default: fprintf(stderr, "Unknown Interrupt: %d, function %d\n", int_num, func_num);
  }
}
