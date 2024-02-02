#include "../exec_Funcs/Dispatcher.h"

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){

	if(arg->type == -1 || arg->type == 11)
		return reg;

	switch(arg->type){

		case global_a :	return &stack[AVM_STACKSIZE - 1 - arg->val];
		case local_a  :	return &stack[topsp - arg->val];
		case formal_a :	return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

		case retval_a:	return &retval;

		case number_a:	{
							reg->type = number_m;
							reg->data.numVal = consts_getnumber(arg->val);
							return reg;
						}

		case string_a:	{
							reg->type = string_m;
							reg->data.strVal = strdup(consts_getstring(arg->val));
							return reg;
						}

		case bool_a:	{
							reg->type = bool_m;
							reg->data.boolVal = arg->val;
							return reg;
						}

		case nil_a:		reg->type = nil_m; return reg;

		case userfunc_a:	{

								reg->type = userfunc_m;
								userfunc* func = avm_getfuncinfo(arg->val);
								reg->data.funcVal = func->address;
								return reg;
							}

		case libfunc_a:		{
								reg->type = libfunc_m;
								reg->data.libfuncVal = libfuncs_getused(arg->val);
								return reg;
							}

		default:			assert(0);

		}
}

double consts_getnumber(unsigned int index){\

	assert(index >= 0 && index < totalNumConsts);
	return numConstsTable[index];

}

char* consts_getstring(unsigned int index){

	assert(index >= 0 && index < totalStrConsts);
	return strConstsTable[index];

}

char* libfuncs_getused(unsigned int index){

	assert(index >= 0 && index < totalLibFuncs);
	return libFuncsTable[index];

}

void initPhase5(void){

	executionFinished = 0 ;
	pc = 0 ;
	currLine = 0 ;
	top = AVM_STACKSIZE - 1 - totalGlobals ;

}

int main(int argc, char **argv){

	char* customName = strdup("");
	int printerino = 0, i = 1, custom = 0;
	while(i <= argc && argv[i] != NULL){

		if(strcmp(argv[i],"-s") == 0){ printf(a_c_r"\nლ(~•̀︿•́~)つ︻̷┻̿═━一 Soupia\n\n"a_c_re); }
		if(strcmp(argv[i],"-p") == 0){ printerino = 1; }
		if(strcmp(argv[i],"-i") == 0){
			printf(a_c_y"| ------------------------------------------ |\n"a_c_re);
			printf(a_c_y"| Compiler by Murtakis, Agelarakis, Tsiakkas |\n"a_c_re);
			printf(a_c_y"| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"a_c_re);
			printf(a_c_y"| Fully functional compiler for alpha        |\n"a_c_re);
			printf(a_c_y"| Made in 2017                               |\n"a_c_re);
			printf(a_c_y"| All rights reserved                        |\n"a_c_re);
			printf(a_c_y"| ------------------------------------------ |\n\n"a_c_re);
		}
		if(strcmp(argv[i],"-n") == 0){
			strcat(customName,argv[i+1]);
			custom = 1;
		}

		i++;

	}

	if(custom == 0) {
		strcat(customName,"AlphaCode");
	}

	DataTables* tables;
	tables = decoder(printerino, customName);

	numConstsTable = tables->numConstsTable;
	totalNumConsts = tables->totalNumConsts;

	strConstsTable = tables->strConstsTable;
	totalStrConsts = tables->totalStrConsts;

	libFuncsTable = tables->libFuncsTable;
	totalLibFuncs = tables->totalLibFuncs;

	userFuncsTable = tables->userFuncsTable;
	totalUserFuncs = tables->totalUserFuncs;

	code = tables->code;
	codeSize = tables->codeSize;

	initPhase5();
	avm_initialize();

	while(executionFinished == 0){
		//printf("Executing instruction %d\n",pc );
		execute_cycle();
	}


}
