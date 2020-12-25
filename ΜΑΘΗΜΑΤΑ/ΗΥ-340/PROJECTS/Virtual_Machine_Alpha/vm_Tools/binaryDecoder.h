#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ConstTablesLinker.h"

#define a_c_r     "\x1b[31m"
#define a_c_g     "\x1b[32m"
#define a_c_y     "\x1b[33m"
#define a_c_b     "\x1b[34m"
#define a_c_m     "\x1b[35m"
#define a_c_c     "\x1b[36m"
#define a_c_re    "\x1b[0m"
#define under     "\e[4m"
#define under_re  "\e[0m"
#define italic    "\e[3m"
#define italic_re "\e[0m"
#define bold      "\e[1m"
#define bold_re   "\e[0m"

typedef struct instructionToBinary instructionToBinary;
typedef struct numberToBinary numberToBinary;
typedef struct stringToBinary stringToBinary;
typedef struct userFuncToBinary userFuncToBinary;
typedef struct libFuncToBinary libFuncToBinary;

struct instructionToBinary{

	int instrOpcode;
	
	int resultType;
	int resultOffset;
	
	int arg1Type;
	int arg1Offset;

	int arg2Type;
	int arg2Offset;

	int instrLine;

};

instructionToBinary instr;

unsigned int 	magicNumberBinary;

double*			numConstsBinary;
unsigned int 	totalNumConstsBinary;

char** 			stringConstsBinary;
unsigned int 	totalStringConstsBinary;

userfunc* 		userFuncsBinary;
unsigned int 	totalUserFuncsBinary;

char**			namedLibFuncsBinary;
unsigned int 	totalNamedLibFuncsBinary;

instruction*	codeTable;
unsigned int 	codeTableSize; 











