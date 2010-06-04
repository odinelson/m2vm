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
#include "m2jit.h"
#include "utils.h"


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


void destroyBuffer(JitBuffer** buffer) {
	free((*buffer)->contents);
	free((*buffer));
	buffer = NULL;
}


void emitByte(JitBuffer* buffer, unsigned char byte) {
	buffer->contents[buffer->idx++] = byte;
}


void genRET(JitBuffer* buffer){
	emitByte(buffer, 0xC3);
}

//OK
void genMOV_REG_IMM(JitBuffer* buffer, int reg, int imm){

	Byte bytes[4];

	int32ToBytes(imm,bytes);

	emitByte(buffer, 0xC7);
	emitByte(buffer, 0xC0 + reg);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);
}

void genADD_REG_IMM(JitBuffer* buffer, int reg, int imm){

	Byte bytes[4];

	unsigned char modrm = (0xc0 + reg);

	int32ToBytes(imm,bytes);

/*	ADD reg, imm */
	emitByte(buffer, 0x81);
	emitByte(buffer, modrm);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);

}
//OK
void genADD_2REG(JitBuffer* buffer, int reg1, int reg2){

	unsigned char modrm = (0xc0 + reg1) | (0xc0 + reg2);

	emitByte(buffer, 0x03);
	emitByte(buffer, modrm);

}

//OK
void genSUB_2REG(JitBuffer* buffer, int reg1, int reg2){

	unsigned char modrm = (0xc0 + reg1) | (0xc0 + reg2);

	/*	MOV reg, reg */
	emitByte(buffer, 0x2B);
	emitByte(buffer, modrm);

}

//OK
void genSUB_REG_IMM(JitBuffer* buffer, int reg, int imm){

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

void genIDIV_REG(JitBuffer* buffer){

	unsigned char modrm = (0xc0 + R_EAX)| (0xc0 + R_EDX) | 0x38;

/*	DIV reg */
	emitByte(buffer, 0xF7);
	emitByte(buffer, modrm);
}

//ok
void genIMUL_REG_IMM(JitBuffer* buffer, int reg, int imm){

	Byte bytes[4];
	int32ToBytes(imm,bytes);

	unsigned char modrm = (0xc0 + reg);

	emitByte(buffer, 0x69);
	emitByte(buffer, modrm);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);
}

void genIMUL_2REG(JitBuffer* buffer, int reg1, int reg2){

	unsigned char modrm = 0xAF | (0xc0 + reg2);

/*	MUL reg */
	emitByte(buffer, 0x0F);
	emitByte(buffer, modrm);
}

int main(void) {

	JitBuffer* code = allocBuffer(4096);

	//Teste ADD OK
	genMOV_REG_IMM(code, R_EAX, 10);
	genADD_REG_IMM(code, R_EAX, 10);
	genRET(code);

	//Teste ADD OK
//	genMOV_REG_IMM(R_EAX, 10,code);
//	genMOV_REG_IMM(R_ECX, 30,code);
//	genADD_2REG(R_EAX,R_ECX,code);
//	genRET(code);


//	//Testando SUB OK
//	genMOV_REG_IMM(R_EAX, 70, code);
//	genSUB_REG_IMM(R_EAX, 8, code);
//	genRET(code);

//	//Testando SUB OK
//	genMOV_REG_IMM(R_EAX, 70, code);
//	genMOV_REG_IMM(R_ECX, 19, code);
//	genSUB_2REG(R_EAX, R_ECX, code);
//	genRET(code);

	//Testando IDIV falhou
//	genMOV_REG_IMM(R_EAX, 10, code);
//	genMOV_REG_IMM(R_EDX, 20, code);
//	genIDIV_2REG(code);
//	genRET(code);


	//Testando IMUL OK
//	genMOV_REG_IMM(R_EAX, 10, code);
//	genIMUL_REG_IMM(R_EAX,100, code);
//	genRET(code);

	//Testando IMUL
//	genMOV_REG_IMM(R_EAX, 10, code);
//	genMOV_REG_IMM(R_ECX,100, code);
//	genIMUL_2REG(R_EAX, R_ECX, code);
//	genRET(code);



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
