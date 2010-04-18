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

void genRET(JitBuffer* buffer);

void genADD_EAX_imm(int imm, JitBuffer* buffer){

	Byte bytes[4];

	int32ToBytes(imm,bytes);

/*	ADD EAX, imm */
	emitByte(buffer, 0x05);
	emitByte(buffer, bytes[0]);
	emitByte(buffer, bytes[1]);
	emitByte(buffer, bytes[2]);
	emitByte(buffer, bytes[3]);

}




int main(void) {
	JitBuffer* code = allocBuffer(10);


	genADD_EAX_imm(1, code);
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
