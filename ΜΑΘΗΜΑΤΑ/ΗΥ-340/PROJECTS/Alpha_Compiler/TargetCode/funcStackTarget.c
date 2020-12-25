#include "targetCode.h"

funcStack* functionStackTarget = NULL;

int isFuncStackTargetEmpty(void){ if(functionStackTarget == NULL) return 1; else return 0; }

void pushFuncStackTarget(SymTableEntry mem){ 

	if(functionStackTarget == NULL){ 

		funcStack *newTop = (funcStack*) malloc (sizeof(funcStack));
		newTop->info = mem;
		newTop->next = NULL;

		functionStackTarget = newTop;

	}else{ 

		funcStack *newTop = (funcStack*) malloc (sizeof(funcStack));
		newTop->info = mem;

		newTop->next = functionStackTarget;
		functionStackTarget = newTop;

	}

}

SymTableEntry popFuncStackTarget(void){

	if(!isFuncStackTargetEmpty()){
		
		funcStack *tmp = functionStackTarget;
		SymTableEntry i = tmp->info;

		functionStackTarget = functionStackTarget->next;

		tmp->next = NULL;
		// thows seg on csd machines free( tmp);

		return i;

	}else{ 

		return NULL;
	
	}
	
}

SymTableEntry topFuncStackTarget(void){

	if(!isFuncStackTargetEmpty()){

		funcStack *tmp = functionStackTarget;
		SymTableEntry i = tmp->info;

		return i;

	}else{

		return NULL;

	}

}

void appendFuncStackTarget(SymTableEntry f, unsigned int instrLabel){

	returnList* newNode = f->value.funcVal->returnList;

	if(newNode == NULL){

		newNode = (returnList*) malloc (sizeof(returnList));	
		newNode -> instrLabel = instrLabel;
		newNode -> next = NULL;
		f->value.funcVal->returnList = newNode;

	}else{

		returnList* tmp = (returnList*) malloc (sizeof(returnList));	
		tmp -> instrLabel = instrLabel;
		tmp -> next = NULL;

		returnList* reader = newNode;
		while(reader->next != NULL){ reader = reader->next; }

		reader -> next = tmp;

	}



}















