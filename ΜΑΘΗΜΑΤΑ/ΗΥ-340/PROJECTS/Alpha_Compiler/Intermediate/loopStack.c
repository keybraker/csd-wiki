#include "phase3.h"

int isLoopStackEmpty(){

	if(loopTop == NULL){
		return 1;
	} 
	return 0;

}


int isBreakListEmpty(){
	if(loopTop->breaklist == NULL){
		return 1;
	}
	return 0;
}


int isContListEmpty(){
	if(loopTop->contlist == NULL){
		return 1;
	}
	return 0;
}


void loopPush(){
	if(isLoopStackEmpty()){
		loopTop = (loopStack*)malloc(sizeof(loopStack));
		loopTop->next = NULL;
		loopTop->breaklist = NULL;
		loopTop->contlist = NULL;
	}
	else{
		loopStack* tmp = (loopStack*)malloc(sizeof(loopStack));
		tmp->next = loopTop;
		tmp->breaklist = NULL;
		tmp->contlist = NULL;
		loopTop = tmp;
	}
}


void breakPush(int QuadNo){
	if(isBreakListEmpty()){
		loopTop->breaklist = (BClist*)malloc(sizeof(BClist));
		loopTop->breaklist->next = NULL;
		loopTop->breaklist->QuadNo = QuadNo;
	}
	else{
		BClist* tmp = (BClist*)malloc(sizeof(BClist));
		tmp->next = loopTop->breaklist;
		tmp->QuadNo = QuadNo;
		loopTop->breaklist = tmp;
	}
}


void contPush(int QuadNo){
	if(isContListEmpty()){
		loopTop->contlist = (BClist*)malloc(sizeof(BClist));
		loopTop->contlist->next = NULL;
		loopTop->contlist->QuadNo = QuadNo;
	}
	else{
		BClist* tmp = (BClist*)malloc(sizeof(BClist));
		tmp->next = loopTop->contlist;
		tmp->QuadNo = QuadNo;
		loopTop->contlist = tmp;
	}
}


loopStack* loopPop(){
	if(isLoopStackEmpty()){
		printf(a_c_r "Error: Trying to pop from empty stack! (LoopStack)");
        printf(a_c_re "\n");
        return NULL;
	}
	else{
		loopStack* tmp = loopTop;
		loopTop = loopTop->next;
		tmp->next = NULL;
		return tmp;
	}
}