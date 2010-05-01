/*
 ============================================================================
 Name        : jit_test.c
 Author      : Odilon
 Version     : 0.0001
 Copyright   : Copyleft
 Description : Prot�tipo de fun��es para gera��o de c�digo JIT (x86)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "utils.h"

/*Registradores*/
#define R_EAX 0
#define R_ECX 1
#define R_EDX 2
#define R_EBX 3
#define R_ESP 4
#define R_EBP 5
#define R_ESI 6
#define R_EDI 7
#define MOD 11


/*
 * Estrutura que representa os dados de um buffer do JIT
 */
typedef struct JitBuffer {
	int idx;
	int size;
	char* contents;
} JitBuffer;

/*
 * Aloca um buffer de tamanho especificado, com o prop�sito de conter o c�digo gerado,
 * e faz uma chamada ao S.O. para dar permiss�o de execu��o ao buffer.
 * Se o buffer, por algum motivo, n�o p�de ser alocado ou tornado execut�vel, retorna NULL;
 * Se tudo correu OK, retorna o buffer alocado.
 *
 * NOTA 1: O buffer � representado como uma estrutura, pois assim podemos ter v�rios
 *         buffers alocados, cada um com seu tamanho e seu contador pr�prios.
 *
 * NOTA 2: No momento, esta implementa��o funciona apenas no MS-Windows
 */
JitBuffer* allocBuffer(int size) {
	DWORD oldProtect;
	JitBuffer* buffer = malloc(sizeof(JitBuffer));
	if (!buffer)
		return NULL;
	buffer->contents = malloc(size);
	if (!buffer->contents)
		return NULL;
	if (!VirtualProtect(buffer->contents, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		free(buffer->contents);
		return NULL;
	}
	buffer->size = size;
	buffer->idx = 0;
	return buffer;
}

/*
 * Desaloca um buffer e seu conte�do, e seta a refer�ncia para NULL.
 * O par�metro � passado por refer�ncia (endere�o do buffer)
 */
void destroyBuffer(JitBuffer** buffer) {
	free((*buffer)->contents);
	free((*buffer));
	buffer = NULL;
}

/*
 * Acrescenta um byte ao buffer, incrementando seu contador.
 * Esta fun��o pode ser usada como "tijolo" para a constru��o das fun��es de
 * gera��o de c�digo JIT.
 * NOTA: Falta fazer a verifica��o de limite (idx extrapolando o tamanho do buffer)
 */
void emitByte(JitBuffer* buffer, unsigned char byte) {
	buffer->contents[buffer->idx++] = byte;
}

/*
 * Tipo que define um ponteiro para fun��o sem par�metros, retornando int.
 */
typedef int (*t_function) (void);

/*
 * Teste-drive: Aqui � gerada uma fun��o que simplesmente retorna o valor 10.
 * pela ABI da linguagem C no x86, EAX � o registrador que cont�m o valor de retorno.
 */


void genRET(JitBuffer* buffer){
	emitByte(buffer, 0xC3);
}

void genMOV_REG_IMM(int reg, int imm, JitBuffer* buffer){

	Byte bytes[4];

	int32ToBytes(imm,bytes);

	emitByte(buffer, 0xC7);
	emitByte(buffer, 0xC0 + reg);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);
}

void genADD_REG_IMM(int reg, int imm, JitBuffer* buffer){

	Byte bytes[4];

	int32ToBytes(imm,bytes);

/*	ADD reg, imm */
	emitByte(buffer, 0x81);
	emitByte(buffer, 0xC0 + reg);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);

}
//PROBLEMA
void genADD_REG_REG(int reg1, int reg2, JitBuffer* buffer){

	unsigned char modrm = reg1 | reg2;

	emitByte(buffer, 0x03);
	emitByte(buffer, modrm);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);

}



void genSUB_REG_IMM(int reg, int imm, JitBuffer* buffer){

	Byte bytes[4];

	unsigned char modrm = (0xc0 + reg) | 0x28;

	int32ToBytes(imm,bytes);


	/*	MOV reg, imm */
	emitByte(buffer, 0x81);
	emitByte(buffer, modrm);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);

}

void genIDIV(int reg, JitBuffer* buffer){

	unsigned char modrm = (0xc0 + reg) | 0x38;

/*	DIV reg */
	emitByte(buffer, 0xF7);
	emitByte(buffer, modrm);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);

}

void genIMUL_REG_IMM(int reg, int imm, JitBuffer* buffer){

	Byte bytes[4];
	int32ToBytes(imm,bytes);


	emitByte(buffer, 0x69);
	emitByte(buffer, reg);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);
}

void genIMUL(int reg, JitBuffer* buffer){

	unsigned char modrm = (0xc0 + reg) | 0x69;

/*	MUL reg */
	emitByte(buffer, 0xf7);
	emitByte(buffer, modrm);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
}

int main(void) {

	JitBuffer* code = allocBuffer(4096);

	//Teste ADD
//	genMOV_REG_IMM(R_EAX, 10,code);
//	genADD_REG_IMM(R_EAX,10,code);
//	genRET(code);

//	//Testando SUB
//	genMOV_REG_IMM(R_EAX, 70, code);
//	genSUB_REG_IMM(R_EAX, 8, code);
//	genRET(code);

	//Testando IMUL
	genMOV_REG_IMM(R_EAX, 10, code);
	genIMUL_REG_IMM(R_EAX,10, code);
	genRET(code);





	/*
	 * Obt�m o conte�do do buffer, fazendo typecast para ponteiro de fun��o,
	 * e executa o mesmo, descartando em seguida.
	 */

	t_function func = (t_function)code->contents;
	int result = func();
	destroyBuffer(&code);

	printf("Resultado: %d\n", result);  /* resultado esperado: 10 */
	return 0;
}
