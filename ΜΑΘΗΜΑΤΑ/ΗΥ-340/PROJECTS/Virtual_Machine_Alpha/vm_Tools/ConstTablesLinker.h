typedef struct DataTables DataTables;
typedef struct userfunc userfunc;

typedef enum vmopcode vmopcode;
typedef enum vmarg_t vmarg_t;
typedef struct vmarg vmarg;
typedef struct instruction instruction;

struct userfunc {

	unsigned int 	address;
	unsigned int 	localSize;
	unsigned int 	totalargs;
	char* 			id;

};

enum vmopcode {

	assign_v,		add_v,				sub_v,
	mul_v,			div_v,				mod_v,
	jump_v,			jeq_v,				jne_v,
	jle_v,			jge_v,				jlt_v,
	jgt_v,			call_v,				pusharg_v,	
	funcenter_v,	funcexit_v,			newtable_v,
	tablegetelem_v,	tablesetelem_v, 	nop_v

};

enum vmarg_t {
	
	invalid 	= -1,
	label_a		= 0,
	global_a 	= 1,
	formal_a	= 2,
	local_a		= 3,
	number_a	= 4,
	string_a	= 5,
	bool_a		= 6,
	nil_a		= 7,
	userfunc_a	= 8,
	libfunc_a	= 9,
	retval_a	= 10,
	nop_a		= 11

};

struct vmarg {

	vmarg_t 		type;
	unsigned int	val;

};

struct instruction {

	vmopcode		opcode;
	vmarg 			result;
	vmarg 			arg1;
	vmarg 			arg2;
	unsigned int 	srcLine;

};

struct DataTables{

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

};

DataTables* decoder(int printerino, char* customName);

unsigned int	totalGlobals; 