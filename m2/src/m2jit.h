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
 * Inicio das fun��es do buffer
 */


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
JitBuffer* allocBuffer(int size);

/*
 * Desaloca um buffer e seu conte�do, e seta a refer�ncia para NULL.
 * O par�metro � passado por refer�ncia (endere�o do buffer)
 */
void destroyBuffer(JitBuffer** buffer);

/*
 * Acrescenta um byte ao buffer, incrementando seu contador.
 * Esta fun��o pode ser usada como "tijolo" para a constru��o das fun��es de
 * gera��o de c�digo JIT.
 * NOTA: Falta fazer a verifica��o de limite (idx extrapolando o tamanho do buffer)
 */
void emitByte(JitBuffer* buffer, unsigned char byte);


/*
 * Tipo que define um ponteiro para fun��o sem par�metros, retornando int.
 */
typedef int (*t_function) (void);


/* Fun��es de gera��o de c�digo */

void genADD_REG_IMM(JitBuffer* buffer, int reg, int imm);
void genADD_2REG(JitBuffer* buffer, int reg1, int reg2);
void genSUB_2REG(JitBuffer* buffer, int reg1, int reg2);
void genSUB_REG_IMM(JitBuffer* buffer, int reg, int imm);
void genIMUL_REG_IMM(JitBuffer* buffer, int reg, int imm);

//Auxiliares
void genRET(JitBuffer* buffer);
void genMOV_REG_IMM(JitBuffer* buffer, int reg, int imm);


