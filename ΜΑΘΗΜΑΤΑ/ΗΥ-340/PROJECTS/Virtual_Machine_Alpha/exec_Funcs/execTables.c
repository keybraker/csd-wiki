#include "Dispatcher.h"

char* typeStringsT[] = {

	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"

};

void execute_newtable (instruction* instr){

	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0 );	
	assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval ));

	avm_memcellClear(lv);

	lv->type			= table_m;
	lv->data.tableVal	= avm_tableNew();
	avm_tableIncRefCounter(lv->data.tableVal);

}

void execute_tablegetelem (instruction* instr){

	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	avm_memcell* t 	= avm_translate_operand(&instr->arg1, 	(avm_memcell*) 0);
	avm_memcell* i  = avm_translate_operand(&instr->arg2, 	&ax );

	assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval ));
	assert(t && (&stack[AVM_STACKSIZE-1] >= t && t > &stack[top] ));
	assert(i);

	avm_memcellClear(lv);
	lv->type = nil_m;
	if(t->type != table_m){
		
		avm_error("Illegal use of type ",typeStringsT[t->type]," as table!");
		executionFinished = 1;
	
	} else {

		avm_memcell* content = avm_tablegetelem(t->data.tableVal , i);
		
		// NEED FIXING PHASE 5 TABLEVAL NOT INSERTED

		if(content){

			avm_assign(lv,content);
		
		} else {

			char* ts = avm_tostring(t);
			char* is = avm_tostring(i);
			
			avm_warning("Index not found! Table: ",ts,is);
			
			//free(ts);
			//free(is); // ta free kanoun problima stin mnimi

		}

	}


}

void execute_tablesetelem (instruction* instr){

	avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*) 0);
	avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
	avm_memcell* c = avm_translate_operand(&instr->result, &bx);

	assert(t && (&stack[AVM_STACKSIZE-1] >= t && t > &stack[top]));
	assert(i && c);

	if(t->type != table_m){
		avm_error("Illegal use of type ",typeStringsT[t->type]," as table!");
		executionFinished = 1;
	}
	else{
		avm_tablesetelem(t->data.tableVal, i, c);
	}

}
































