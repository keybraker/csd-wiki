#include "Dispatcher.h"

void execute_call			(instruction* instr){

	avm_memcell* func = avm_translate_operand(&instr->result, &ax);
	assert(func);

	avm_callSaveEnvironment();

	switch(func->type){
		case userfunc_m:	{
								pc = func->data.funcVal;
								assert(pc < AVM_ENDING_PC);
								assert(code[pc].opcode == funcenter_v);
								break;
							}
		
		case string_m: 		avm_callLibFunc(func->data.strVal); break;
		
		case libfunc_m:		avm_callLibFunc(func->data.libfuncVal); break;

		default:			{
								char* s = avm_tostring(func);
								avm_error("Call : cannot bind '",s,"' to function!");
								//free(s);
								executionFinished = 1;
							}

	}

}

void execute_pusharg		(instruction* instr){

	avm_memcell* arg = avm_translate_operand(&instr->result, &ax);
	assert(arg);

	avm_assign(&stack[top] , arg);
	++totalActuals;
	avm_dec_top();

}

void execute_funcenter		(instruction* instr){

	avm_memcell* func	= avm_translate_operand(&instr->result, &ax);
	assert(func);
	assert(pc == func->data.funcVal);

	totalActuals = 0;

	userfunc* funcInfo 	= avm_getfuncinfo(code[pc].result.val);
	topsp				= top;
	top					= top - funcInfo->localSize;

	
	if( avm_totalactuals() != 0  && funcInfo->totalargs != 0 && (avm_totalactuals() < funcInfo->totalargs) ){

		avm_error("Too few arguments for function ", funcInfo->id, NULL);
		executionFinished = 1;
		exit(0);
		
	}
	//printf("Args send to func %s are %d and func must get %d args\n",funcInfo->id ,avm_totalactuals() , funcInfo->totalargs);

}

void execute_funcexit		(instruction* instr){

	unsigned int oldTop = top;
	top 	= avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	pc 		= avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp 	= avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

	while(++oldTop <= top){

		avm_memcellClear(&stack[oldTop]);

	}

}
























