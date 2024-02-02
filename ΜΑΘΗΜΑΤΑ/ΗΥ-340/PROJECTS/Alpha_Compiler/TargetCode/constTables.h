#include "targetCode.h"

#define EXPAND_SIZE 1024

#define CURR_SIZE_NUM (totalNumConsts * sizeof(double))
#define NEW_SIZE_NUM (EXPAND_SIZE * sizeof(double) + CURR_SIZE_NUM)

#define CURR_SIZE_STR (totalStringConsts * sizeof(char *))
#define NEW_SIZE_STR (EXPAND_SIZE * sizeof(char *) + CURR_SIZE_STR)

#define CURR_SIZE_LIBFUNC (totalNamedLibFuncs * sizeof(char *))
#define NEW_SIZE_LIBFUNC (EXPAND_SIZE * sizeof(char *) + CURR_SIZE_LIBFUNC)

#define CURR_SIZE_USERFUNC (totalUserFuncs * sizeof(userfunc))
#define NEW_SIZE_USERFUNC (EXPAND_SIZE * sizeof(userfunc) + CURR_SIZE_USERFUNC)

#define CURR_SIZE_INSTR_ARR (totalInstrSize * sizeof(instruction))
#define NEW_SIZE_INSTR_ARR (EXPAND_SIZE * sizeof(instruction) + CURR_SIZE_INSTR_ARR)

typedef enum TYPER
{
	NUMBER_T,
	STRINGER_T,
	LIBFUNCER_T,
	USERFUNCER_T,
	INSTRUCTER_T
} TYPER;

int totalNumSize;
int totalStringSize;
int totalLibFuncSize;
int totalUserFuncSize;
int totalInstrSize;

void EXPANDER(TYPER type);

int INSERTER_NUM(double val);
int INSERTER_STRING(char *val);
int INSERTER_LIBFUNC(char *val);
int INSERTER_USERFUNC(unsigned int address, unsigned int localSize, unsigned int totalargs, char *id);
// int INSERTER_INSTR_ARR (vmopcode opcode, vmarg result, vmarg arg1, vmarg arg2, unsigned int srcLine); // tin ekana emitInstr giati einai allou
//  papa evagelio
int emitInstr(instruction t); // When I wrote this, only God and I understood what I was doing
							  // Now, God only knows (ノ͡° ͜ʖ ͡°)ノ︵┻┻

void PRINTER_USERFUNC();
void PRINTER_STR();
void PRINTER_NUM();
void PRINTER_LIB();
