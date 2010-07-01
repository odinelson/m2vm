 /*
 ============================================================================
 Name        : jit_test.c
 Author      : Odilon
 Version     : 0.0001
 Copyright   : Copyleft
 Description : Protótipo de funções para geração de código JIT (x86)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "m2jit.h"
// FIXME windows.h defines an 'INT' symbol... cannot use opcodes.h
///#include "opcodes.h"
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

int isJittable(unsigned char op) {
	///return op >= INC && op <= DIV;
	// FIXME windows.h defines an 'INT' symbol... cannot use opcodes.h
	return op >= 0x02 && op <= 0x08;
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

int execBuffer(JitBuffer* buffer){

	t_function func = (t_function)buffer->contents;
	return func();

}
