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
 * Aloca um buffer de tamanho especificado, com o propósito de conter o código gerado,
 * e faz uma chamada ao S.O. para dar permissão de execução ao buffer.
 * Se o buffer, por algum motivo, não pôde ser alocado ou tornado executável, retorna NULL;
 * Se tudo correu OK, retorna o buffer alocado.
 *
 * NOTA 1: O buffer é representado como uma estrutura, pois assim podemos ter vários
 *         buffers alocados, cada um com seu tamanho e seu contador próprios.
 *
 * NOTA 2: No momento, esta implementação funciona apenas no MS-Windows
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
 * Desaloca um buffer e seu conteúdo, e seta a referência para NULL.
 * O parâmetro é passado por referência (endereço do buffer)
 */
void destroyBuffer(JitBuffer** buffer) {
	free((*buffer)->contents);
	free((*buffer));
	buffer = NULL;
}

/*
 * Acrescenta um byte ao buffer, incrementando seu contador.
 * Esta função pode ser usada como "tijolo" para a construção das funções de
 * geração de código JIT.
 * NOTA: Falta fazer a verificação de limite (idx extrapolando o tamanho do buffer)
 */
void emitByte(JitBuffer* buffer, unsigned char byte) {
	buffer->contents[buffer->idx++] = byte;
}

/*
 * Tipo que define um ponteiro para função sem parâmetros, retornando int.
 */
typedef int (*t_function) (void);

/*
 * Teste-drive: Aqui é gerada uma função que simplesmente retorna o valor 10.
 * pela ABI da linguagem C no x86, EAX é o registrador que contém o valor de retorno.
 */

int decTobin(int number) {
	int x, y, k[2];
	char str[2];
	x = y = 0;

	for(y = 2; y >= 0; y--) {
		x = number / (1 << y);
		number = number - x * (1 << y);
		k[y-1] = x;
	}
	sprintf(str,"%d%d%d", k[1],k[0],k[-1]);
	return atoi(str);
}


void binTohexa(int bin){
	char inst[1];
	int i=0,a[5],t=0;
	long int n = bin;
	while(n!=0)
	{
		a[i]=n%10000;
		n=n/10000;
		if(a[i]>1111)
			t=1;
		i++;
	}
	i--;
	if(t==0)
		for(;i>=0;i--)
		{
			switch(a[i])
			{
			case 0:
				inst[i] = '0';
				break;
			case 1:
				inst[1-i] = '1';
				break;
			case 10:
				inst[1-i] = '2';
				break;
			case 11:
				inst[1-i] = '3';
				break;
			case 100:
				inst[1-i] = '4';
				break;
			case 101:
				inst[1-i] = '5';
				break;
			case 110:
				inst[1-i] = '6';
				break;
			case 111:
				inst[1-i] = '7';
				break;
			case 1000:
				inst[1-i] = '8';
				break;
			case 1001:
				inst[1-i] = '9';
				break;
			case 1010:
				inst[1-i] = 'A';
				break;
			case 1011:
				inst[1-i] = 'B';
				break;
			case 1100:
				inst[1-i] = 'C';
				break;
			case 1101:
				inst[1-i] = 'D';
				break;
			case 1110:
				inst[1-i] = 'E';
				break;
			case 1111:
				inst[1-i] = 'F';
				break;
			default:
				printf("\n");
				break;
			}
		}
	if(t==1)
		printf("Numero não é binario\n");

	printf(inst);
	//TODO: Retorno dando pau!!!!
}


void genMOD_RM(int secOpcode, int reg1){

	int x = decTobin(secOpcode);
//	char str = "";
	int reg = 0;

	switch (reg) {
		case 0:
			reg = 000;
			break;
		case 1:
			reg = 001;
			break;
		case 2:
			reg = 010;
			break;
		case 3:
			reg = 011;
			break;
		case 4:
			reg = 100;
			break;
		case 5:
			reg = 101;
			break;
		case 6:
			reg = 110;
			break;
		case 7:
			reg = 111;
			break;
		default:
			break;
	}

//	sprintf(str, "%d%d%d", MOD, x, reg);
//	int c = atoi(str);
//	printf("%d",c);
}

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


void genSUB_REG_IMM(int reg, int imm, JitBuffer* buffer){

	Byte bytes[4];

	int32ToBytes(imm,bytes);


	/*	MOV reg, imm */
	emitByte(buffer, 0x81);
	emitByte(buffer, 0xE8);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);

}

void genIDIV(int reg, JitBuffer* buffer){

/*	DIV reg */
	emitByte(buffer, 0xF7);
	emitByte(buffer, 0xF8);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);

}

void genIMUL(int reg, JitBuffer* buffer){

/*	MUL reg */
	emitByte(buffer, 0xF7);
	emitByte(buffer, 0xE8);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);
	emitByte(buffer, 0x00);

}


int main(void) {

//	JitBuffer* code = allocBuffer(4096);

//	//Testando SUB
//	genMOV_REG_IMM(R_EAX, 70, code);
//	genSUB_REG_IMM(R_EAX, 8, code);

//	Teste ADD
//	genMOV_REG_IMM(R_EAX, 0, code);
//	genMOV_REG_IMM(R_EAX,0,code);

//	//Teste IDIV
//	genMOV_REG_IMM(R_EAX, 10, code);
//	genMOV_REG_IMM(R_EDX, 10, code);
//	genIDIV(R_EAX, code);

	//Teste IMUL
//	genMOV_REG_IMM(R_EAX, 10,code);
//	genIMUL(R_EAX, code);


	genMOD_RM(7,R_EAX);

	/*
	 * Obtém o conteúdo do buffer, fazendo typecast para ponteiro de função,
	 * e executa o mesmo, descartando em seguida.
	 */

//	t_function func = (t_function)code->contents;
//	int result = func();
//	destroyBuffer(&code);
//
//	printf("Resultado: %d\n", result);  /* resultado esperado: 10 */
//	return 0;
}
