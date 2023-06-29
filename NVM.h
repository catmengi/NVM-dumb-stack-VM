#define STACK_SIZE 32768
#define DEBUG false
#define DYN_VAR true
#define DYN_MEM false
#define sRAM_SIZE 32768
#define MAX_AMOUNT_OF_INSTRUCTIONS 65536
#define MAX_AMOUNT_OF_FUNC 65536
#include <stdlib.h>
typedef enum OPCODES{
PUSH,
POPR,
PUSR,
SCAL,
ADDS,
MINS,
MULS,
DIVS,
JUMP,
VARC,
VARR,
VARE,
VARD,
IFEE,
IFNE,
ADDO,
MINO,
HALT,
FORE
}OPCODES;
int SP;
int STACK[STACK_SIZE];
int IP;
typedef struct OPCODEFLOW{
OPCODES OPCODE;
int ARGS[4];
}OPCODEFLOW;
OPCODEFLOW OPCODEFLOWE[MAX_AMOUNT_OF_INSTRUCTIONS];
int FUNCS[MAX_AMOUNT_OF_FUNC][3];
int VARCODES[65536][2];
int VARS[65536];
int LFV;
int LFVC;
int sRAM[sRAM_SIZE];
//int VARSCURSIZE;
typedef unsigned short WORD;
