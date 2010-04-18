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
	 * Obtém o conteúdo do buffer, fazendo typecast para ponteiro de função,
	 * e executa o mesmo, descartando em seguida.
	 */

	t_function func = (t_function)code->contents;
	int result = func();
	destroyBuffer(&code);

	printf("Resultado: %d\n", result);  /* resultado esperado: 10 */
	return 0;
}
