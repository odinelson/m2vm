/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "opcodes.h"
#include "exec.h"  /*para enxergar os registradores (talvez seja melhor fazer outro arquivo, com a definição das estruturas da maquina...)*/

Byte* ram;
int ramSize;

char* REG_NAME[] = { "R0", "R1", "R2", "R3", "R4", "R5", "FR", "IR", "MR", "DT", "UD", "ST", "SB", "SP", "FP", "IP" };

Int16 bytesToInt16(Byte bytes[]) {
  Int16 i;
  memcpy(&i, bytes, sizeof(Int16));
  return i;
}

Int32 bytesToInt32(Byte bytes[]) {
  Int32 i;
  memcpy(&i, bytes, sizeof(Int32));
  return i;
}

Real32 bytesToFloat(Byte bytes[]) {
  Real32 f;
  memcpy(&f, bytes, sizeof(Real32));
  return f;
}

void int16ToBytes(Int16 i, Byte bytes[]) {
  memcpy(bytes, &i, sizeof(Int16));
}

void int32ToBytes(Int32 i, Byte bytes[]) {
  memcpy(bytes, &i, sizeof(Int32));
}

void floatToBytes(Real32 f, Byte bytes[]) {
  memcpy(bytes, &f, sizeof(Real32));
}

char* readStr_(char* prompt, char* str, int maxSize) {
  if (maxSize == -1)
	  maxSize = 1024;
  if (prompt != NULL)
	  printf(prompt);
  fflush(stdout);  /*even without a prompt, something might have been put to screen ...*/
  char* ptr = fgets(str, maxSize, stdin);
  int last = strlen(ptr)-1;
  /* remove trailing newline */
  if (ptr[last] == '\n')
	  ptr[last] = '\0';
  return ptr;
}

int loadToRAM(char* exeName) {
  M2ExeHdr hdr;
  /**printf("**DBG: sizeof(M2ExeHdr) = %d\n", sizeof(M2ExeHdr));*/
  FILE* arq = fopen(exeName, "rb");
  if (!arq) return 0;
  fread(&hdr, sizeof(M2ExeHdr), 1, arq);
  /*check exe signature*/
  if (hdr.signature[0] != 'M' || hdr.signature[1] != '2') {
    fprintf(stderr, "Invalid Binary.\n");
    exit(1);
  }
  else if (hdr.versionMajor != M2_VERSION_MAJOR || hdr.versionMinor != M2_VERSION_MINOR) {
    fprintf(stderr,
            "Incorrect VM version.\nFound: %d.%d\nExpected: %d.%d\n",
            hdr.versionMajor, hdr.versionMinor, M2_VERSION_MAJOR, M2_VERSION_MINOR);
    exit(1);
  }

  DBG("Code Size=%d bytes", hdr.codeSize);
  DBG("Data Size=%d bytes", hdr.dataSize);
  DBG("Uninitialized Data Size=%d bytes", hdr.nonInitDataSize);
  DBG("Stack Size=%d bytes", hdr.stackSize);

  /*init RAM*/
  ramSize = M2_DEFAULT_RAM_SIZE;
  if ((hdr.codeSize + hdr.dataSize + hdr.nonInitDataSize + hdr.stackSize) > ramSize) {
    fprintf(stderr, "Not enough memory.\n");
    exit(-1);
  }
  ram = (Byte*)malloc(ramSize);
/**  memset(ram, 0, ramSize);*/  /*não zerar a RAM... dados não-inicializados contém bytes aleatórios.*/
  DBG("Total de RAM alocada=%d bytes  (0x%X)", ramSize, ramSize);

  /*copia o segmento de código e o de dados inicializados*/
  fread(ram, sizeof(Byte), hdr.codeSize + hdr.dataSize, arq);
  fclose(arq);

  /*Inicializa os registradores de segmento*/
  DT = hdr.codeSize;
  UD = DT + hdr.dataSize;
  SP = SB = ramSize;
  ST = ramSize - hdr.stackSize;

  DBG("** Stack starts at %d, with size %d", ramSize, hdr.stackSize);

  return 1;
}

static char* asAscii(Byte b) {
  static char buff[4];
  if (b == '\n') return "\'\\n\'";
  if (b == '\t') return "\'\\t\'";
  if (b == '\b') return "\'\\b\'";
  if (b == '\a') return "\'\\a\'";
  if (b == 0) return "\'\\0\'";
  sprintf(buff, "\'%c\'", b);
  return buff;
}

void showIntRegisters() {
  int i;
  printf("Int Registers:\n");
  for (i = 0; i < 16; i++)
    printf("%s\t= %4d\t(dec); %08X\t(hex); %s\t(ascii)\n", REG_NAME[i], (int)reg_i[i], (unsigned)reg_i[i], asAscii(reg_i[i]));
  printf("\n");
}

void showFloatRegisters() {
  int i;
  printf("Float Registers:\n");
  for (i = 0; i < 6; i++)
    printf("F%02d = %f (dec); %08X (hex)\n", i, reg_f[i], (unsigned)reg_f[i]);
  printf("\n");
}

void dumpRAM(int start, int end, int as_words) {
  int i;
  if (as_words) {  /*mostra a RAM como Words (32 bits)*/
     for (i = start; i < end; i+=WORD_SIZE)
       printf("[%08X]\t%10d  (dec);\t%04X  (hex)\n", i, bytesToInt16(&ram[i]), bytesToInt16(&ram[i]));
  }
  else {
    for (i = start; i < end; i++)
      printf("[%08X]\t%3d  (dec);\t%02X  (hex);\t%s  (ascii)\n", i, ram[i], ram[i], asAscii(ram[i]));
  }
  printf("\n");
}
