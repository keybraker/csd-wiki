#include "Dispatcher.h"

void execute_jeq (instruction* instr){

	assert(instr->result.type == label_a);

	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in equality",NULL,NULL);
		executionFinished = 1;
	}else if (rv1->type == nil_m || rv2->type == nil_m){
		result = (rv1->type == nil_m) && (rv2->type == nil_m);
	}else if(rv1->type == bool_m || rv2->type == bool_m){
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		avm_error("Equality check between different types is illegal",NULL,NULL);
		executionFinished = 1;
	}else{

 		if(rv1->type == number_m){
			result = rv1->data.numVal == rv2->data.numVal;
		}else if(rv1->type == string_m){
			result = !strcmp(rv1->data.strVal,rv2->data.strVal);
		}else{
			result = (avm_tobool(rv1) == avm_tobool(rv2));
		}

	}

	if(!executionFinished && result)
		pc = instr->result.val;
	
}

void execute_jne (instruction* instr){
	
	assert(instr->result.type == label_a);

	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in equality",NULL,NULL);
		executionFinished = 1;
	}else if (rv1->type == nil_m || rv2->type == nil_m){
		result = (rv1->type == nil_m) && (rv2->type == nil_m);
	}else if(rv1->type == bool_m || rv2->type == bool_m){
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		avm_error("Equality check between different types is illegal",NULL,NULL);
		executionFinished = 1;
	}else{
		if(rv1->type == number_m){
			result = rv1->data.numVal == rv2->data.numVal;
		}else if(rv1->type == string_m){
			result = !strcmp(rv1->data.strVal,rv2->data.strVal); 
		}else{
			result = (avm_tobool(rv1) == avm_tobool(rv2));
		}
	}

	if(!executionFinished && !result)
		pc = instr->result.val;

}

void execute_jump (instruction* instr){

	assert(instr->result.type == label_a);

	if(!executionFinished)
		pc = instr->result.val;

}


