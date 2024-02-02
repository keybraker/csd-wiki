#include "operands.h"

typedef struct instructionToBinary instructionToBinary;
typedef struct numberToBinary numberToBinary;
typedef struct stringToBinary stringToBinary;
typedef struct userFuncToBinary userFuncToBinary;
typedef struct libFuncToBinary libFuncToBinary;

struct instructionToBinary
{

	int instrOpcode;

	int resultType;
	int resultOffset;

	int arg1Type;
	int arg1Offset;

	int arg2Type;
	int arg2Offset;

	int instrLine;
};

// struct numberToBinary{

// 	int offset;
// 	int value;

// };

// struct stringToBinary{

// 	int offset;
// 	char* value;

// };

// struct userFuncToBinary{

// 	int offset;
// 	int address;
// 	int localSize;
// 	char* id;

// };

// struct libFuncToBinary{

// 	int offset;
// 	char* value;

// };
