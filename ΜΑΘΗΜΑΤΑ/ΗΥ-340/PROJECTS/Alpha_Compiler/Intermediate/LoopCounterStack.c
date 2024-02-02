#include "phase3.h"

int isLoopCounterStackEmpty()
{
	if (loopCounterStack == NULL)
		return 1;
	else
		return 0;
}

void pushLoopCounter(int mem)
{

	if (loopCounterStack == NULL)
	{

		myStack *newTop = (myStack *)malloc(sizeof(myStack));
		newTop->info = mem;
		newTop->next = NULL;

		loopCounterStack = newTop;
	}
	else
	{

		myStack *newTop = (myStack *)malloc(sizeof(myStack));
		newTop->info = mem;

		newTop->next = loopCounterStack;
		loopCounterStack = newTop;
	}
}

int popLoopCounter()
{

	if (!isLoopCounterStackEmpty())
	{

		myStack *tmp = loopCounterStack;
		int i = tmp->info;

		loopCounterStack = loopCounterStack->next;

		tmp->next = NULL;
		// thows seg on csd machines free(tmp);

		return i;
	}
	else
	{
		return -1;
	}
}
