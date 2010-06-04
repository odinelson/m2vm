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
 * Inicio das funções do buffer
 */


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
JitBuffer* allocBuffer(int size);

/*
 * Desaloca um buffer e seu conteúdo, e seta a referência para NULL.
 * O parâmetro é passado por referência (endereço do buffer)
 */
void destroyBuffer(JitBuffer** buffer);

/*
 * Acrescenta um byte ao buffer, incrementando seu contador.
 * Esta função pode ser usada como "tijolo" para a construção das funções de
 * geração de código JIT.
 * NOTA: Falta fazer a verificação de limite (idx extrapolando o tamanho do buffer)
 */
void emitByte(JitBuffer* buffer, unsigned char byte);


/*
 * Tipo que define um ponteiro para função sem parâmetros, retornando int.
 */
typedef int (*t_function) (void);


/* Funções de geração de código */

void genADD_REG_IMM(JitBuffer* buffer, int reg, int imm);
void genADD_2REG(JitBuffer* buffer, int reg1, int reg2);
void genSUB_2REG(JitBuffer* buffer, int reg1, int reg2);
void genSUB_REG_IMM(JitBuffer* buffer, int reg, int imm);
void genIMUL_REG_IMM(JitBuffer* buffer, int reg, int imm);

//Auxiliares
void genRET(JitBuffer* buffer);
void genMOV_REG_IMM(JitBuffer* buffer, int reg, int imm);


