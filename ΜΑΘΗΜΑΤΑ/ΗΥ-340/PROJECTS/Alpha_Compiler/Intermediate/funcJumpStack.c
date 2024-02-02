#include "phase3.h"

int isFuncJumpStackEmpty()
{
	if (functionJumpStack == NULL)
		return 1;
	else
		return 0;
}

void pushFuncJump(int mem)
{

	if (functionJumpStack == NULL)
	{

		myStack *newTop = (myStack *)malloc(sizeof(myStack));
		newTop->info = mem;
		newTop->next = NULL;

		functionJumpStack = newTop;
	}
	else
	{

		myStack *newTop = (myStack *)malloc(sizeof(myStack));
		newTop->info = mem;

		newTop->next = functionJumpStack;
		functionJumpStack = newTop;
	}
}

int popFuncJump()
{

	if (!isFuncJumpStackEmpty())
	{

		myStack *tmp = functionJumpStack;
		int i = tmp->info;

		functionJumpStack = functionJumpStack->next;

		tmp->next = NULL;
		// thows seg on csd machines free( tmp);

		return i;
	}
	else
	{
		return -1;
	}
}
