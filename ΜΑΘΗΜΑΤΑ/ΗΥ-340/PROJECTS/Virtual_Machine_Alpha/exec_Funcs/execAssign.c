#include "Dispatcher.h"

void execute_assign(instruction *instr)
{

	avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
	avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);

	assert(lv);
	assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
	assert(rv);

	avm_assign(lv, rv);
}