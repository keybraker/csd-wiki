#include "memManager.h"

#define AVM_STACKENV_SIZE	4

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned int top, topsp;

unsigned char	executionFinished ;
unsigned int 	pc ;
unsigned int 	currLine ;

double* numConstsTable;
unsigned int totalNumConsts;

char** strConstsTable;
unsigned int totalStrConsts;

char** libFuncsTable;
unsigned int totalLibFuncs;

userfunc* userFuncsTable;
unsigned int totalUserFuncs;

instruction* code;
unsigned int codeSize;

#define AVM_ENDING_PC codeSize

double consts_getnumber(unsigned int index);
char*  consts_getstring(unsigned int index);
char*  libfuncs_getused(unsigned int index);

void initPhase5(void);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);