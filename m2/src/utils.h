/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#define M2_VERSION_MAJOR  0
#define M2_VERSION_MINOR  9
/* Default RAM size: 256KB. TODO: Command-line param to specify other amount of memory. */
#define M2_DEFAULT_RAM_SIZE  (256 * 1024)

typedef signed short Int16;
typedef signed int Int32;
typedef float Real32;
typedef unsigned char Byte;


#ifdef  DEBUG
/*Macro para debug, com número variável de argumentos (sintaxe padrão C99):*/
#define DBG(fmt, ...)   printf("DEBUG: "fmt"\n", ## __VA_ARGS__)
/* __VA_ARGS__ será substituído pelos parâmetros dados. E o ## entre a vírgula e __VA_ARGS__
   se encarregará de remover a vírgula quando o número de argumentos for 0.
*/
#else

#define DBG(fmt, ...)

#endif  /*DEBUG*/

typedef struct M2ExeHdr {
  Byte signature[2];
  Byte versionMajor, versionMinor;
  Int32 codeSize;
  Int32 dataSize;
  Int32 nonInitDataSize;
  Int32 stackSize;
  /*for future use*/
  Byte reserved[8];
} M2ExeHdr;

/* Extract nibbles from a byte */
#define HI_NIBBLE(arg)    (((arg)&0xF0)>>4)
#define LO_NIBBLE(arg)    ((arg)&0x0F)

/* Extract bytes from a halfword */
#define HI_BYTE(arg)    (((arg)&0xFF00)>>8)
#define LO_BYTE(arg)    ((arg)&0x00FF)

/* Extract halfwords from a word */
#define HI_HALFWORD(arg)    (((arg)&0xFFFF0000)>>16)
#define LO_HALFWORD(arg)    ((arg)&0x0000FFFF)

/* Individual bit manipulation (assumes byte operands) */
#define TEST_BITS(byte,mask)    ((byte)&(mask))
#define SET_BITS(byte,mask)     ((byte) |= (mask))
#define CLEAR_BITS(byte,mask)   ((byte) &= ~(mask))

/*transformar o nome de um macro ou identificador em string*/
#define STR(id)  #id

extern char* REG_NAME[];

Int16 bytesToInt16(Byte bytes[]);
Int32 bytesToInt32(Byte bytes[]);
Real32 bytesToFloat(Byte bytes[]);

void int16ToBytes(Int16 i, Byte bytes[]);
void int32ToBytes(Int32 i, Byte bytes[]);
void floatToBytes(Real32 f, Byte bytes[]);

/* avoid gets, simplify fgets */
char* readStr_(char* prompt, char* str, int maxSize);

/* convenience, for when we don't want a prompt */
#define readStrPrompt(prompt, str, maxSize)  readStr_(prompt, str, maxSize)
#define readStr(str, maxSize)  readStr_(NULL, str, maxSize)

int loadToRAM(char* exeName);
void showIntRegisters();
void showFloatRegisters();
void dumpRAM(int start, int end, int as_words);

extern Byte* ram;
extern int ramSize;

#ifdef __cplusplus
}
#endif

#endif /*UTILS_H*/
