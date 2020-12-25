#include "phase3.h"

int isStackEmpty(){ if(functionLocalsStack == NULL) return 1; else return 0; }


void push(int mem){ 

	if(functionLocalsStack == NULL){ 

		myStack *newTop = (myStack*) malloc (sizeof(myStack));
		newTop->info = mem;
		newTop->next = NULL;

		functionLocalsStack = newTop;

	}else{ 

		myStack *newTop = (myStack*) malloc (sizeof(myStack));
		newTop->info = mem;

		newTop->next = functionLocalsStack;
		functionLocalsStack = newTop;

	}

}

int pop(void){

	if(!isStackEmpty()){
		
		myStack *tmp = functionLocalsStack;
		int i = tmp->info;

		functionLocalsStack = functionLocalsStack->next;

		tmp->next = NULL;
		// thows seg on csd machines free( tmp);

		return i;

	}else{
		return -1;
	}
	
}

