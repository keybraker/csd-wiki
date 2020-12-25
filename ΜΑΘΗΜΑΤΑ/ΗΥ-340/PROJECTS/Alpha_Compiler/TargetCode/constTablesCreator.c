#include "constTables.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void EXPANDER (TYPER type) {

	switch(type){
		case NUMBER_T:
						assert(totalNumConsts == totalNumSize);
						double* p = (double*) malloc (NEW_SIZE_NUM);
						if(numConsts){
							memcpy(p, numConsts, CURR_SIZE_NUM);
							free(numConsts);
						}
						numConsts = p;
						totalNumSize += EXPAND_SIZE;
						break;

		case STRINGER_T:
						assert(totalStringConsts == totalStringSize);
						char** p1 = (char**) malloc (NEW_SIZE_STR);
						if(stringConsts){
							memcpy(p1, stringConsts, CURR_SIZE_STR);
							free(stringConsts);
						}
						stringConsts = p1;
						totalStringSize += EXPAND_SIZE;
						break;

		case LIBFUNCER_T:
						assert(totalLibFuncSize == totalNamedLibFuncs);
						char** p2 = (char**) malloc (NEW_SIZE_LIBFUNC);
						if(namedLibFuncs){
							memcpy(p2, namedLibFuncs, CURR_SIZE_LIBFUNC);
							free(namedLibFuncs);
						}
						namedLibFuncs = p2;
						totalLibFuncSize += EXPAND_SIZE;
						break;

		case USERFUNCER_T:
						assert(totalUserFuncs == totalUserFuncSize);
						userfunc* p3 = (userfunc*) malloc (NEW_SIZE_USERFUNC);
						if(userFuncs){
							memcpy(p3, userFuncs, CURR_SIZE_USERFUNC);
							free(userFuncs);
						}
						userFuncs = p3;
						totalUserFuncSize += EXPAND_SIZE;
						break;

		case INSTRUCTER_T:
						assert(totalInstructions == totalInstrSize);
						instruction* p4 = (instruction*) malloc (NEW_SIZE_INSTR_ARR);
						if(instructions){
							memcpy(p4, instructions, CURR_SIZE_INSTR_ARR);
							free(instructions);
						}
						instructions = p4;
						totalInstrSize += EXPAND_SIZE;
						break;

		default : 		assert(0); break;
	}
	
}

int INSERTER_NUM (double val) {

	int i = 0; for(;i<totalNumConsts;i++){ if(numConsts[i] == val){ return i;} }

	if (totalNumSize == totalNumConsts)
		EXPANDER(NUMBER_T); 

	int position = totalNumConsts;

	numConsts[totalNumConsts++]	= val;

	return position;

}

int INSERTER_STRING (char* val) {

	int i = 0; for(;i<totalStringConsts;i++){ if(strcmp(stringConsts[i],val) == 0){ return i;} }

	if (totalStringSize == totalStringConsts)
		EXPANDER(STRINGER_T); 

	int position = totalStringConsts;

	stringConsts[totalStringConsts++] = (char*) strdup(val);

	return position;

}

int INSERTER_LIBFUNC (char* val) {

	int i = 0; for(;i<totalNamedLibFuncs;i++){ if(strcmp(namedLibFuncs[i],val) == 0){ return i;} }

	if (totalLibFuncSize == totalNamedLibFuncs)
		EXPANDER(LIBFUNCER_T); 

	int position = totalNamedLibFuncs;

	namedLibFuncs[totalNamedLibFuncs++]	= (char*) strdup(val);

	return position;

}

int INSERTER_USERFUNC (unsigned int address, unsigned int localSize, unsigned int totalargs, char* id){

	int i = 0; 

	for(;i<totalUserFuncs;i++){ 
		if(strcmp(userFuncs[i].id , id) == 0 && userFuncs[i].address == address){
			 return i;
		} 
	}

	if(totalUserFuncSize == totalUserFuncs)
		EXPANDER(USERFUNCER_T);

	int position = totalUserFuncs;

	userfunc* p = userFuncs + totalUserFuncs++;

	p -> address	=	address;
	p -> localSize	=	localSize;
	p -> totalargs 	= 	totalargs;
	p -> id 		=	id;
	
	return position;

}

int emitInstr (instruction t){

	if(totalInstrSize == totalInstructions)
		EXPANDER(INSTRUCTER_T);

	int position = totalInstructions;

	instruction* p = instructions + totalInstructions++;
	
	p -> opcode 	= t . opcode;
	p -> result 	= t . result;
	p -> arg1 		= t . arg1;
	p -> arg2 		= t . arg2;
	p -> srcLine	= t . srcLine;

	return totalInstructions;
}

void PRINTER_NUM(void){

	int i = 0;
	printf(a_c_r bold under"PINAKAS ARITHMITIKON STATHERON\n"under_re bold_re a_c_re);

	for(i = 0; i<totalNumConsts; i++){
		printf(a_c_b "|" a_c_re);
		printf(a_c_b italic "%d" italic_re a_c_re, i);
		printf(a_c_b "| %lf\n" a_c_re, numConsts[i]);
	}
	printf("\n");

} 

void PRINTER_STR(void){

	int i = 0;
	printf(a_c_r bold under"PINAKAS STATHERON STRINGS\n"under_re bold_re a_c_re);

	for(i = 0; i<totalStringConsts; i++){
		printf(a_c_b "|" a_c_re);
		printf(a_c_b italic "%d" italic_re a_c_re, i);
		printf(a_c_b "| %s\n" a_c_re, stringConsts[i]);
	}
	printf("\n");
}

void PRINTER_USERFUNC(void){

	int i = 0;
	printf(a_c_r bold under"PINAKAS SUNARTISEON XRISTI\n"under_re bold_re a_c_re);

	for(i = 0; i<totalUserFuncs; i++){
		printf(a_c_b "|" a_c_re);
		printf(a_c_b italic "%d" italic_re a_c_re, i);
		printf(a_c_b "| address %d, localSize %d, id %s\n" a_c_re,userFuncs[i].address,userFuncs[i].localSize,userFuncs[i].id);
	}
	printf("\n");

}

void PRINTER_LIB(void){

	int i = 0;
	printf(a_c_r bold under"PINAKAS SUNARTISEON VIVLIOTHIKIS\n"under_re bold_re a_c_re);

	for(i = 0; i<totalNamedLibFuncs; i++){
		printf(a_c_b "|" a_c_re);
		printf(a_c_b italic "%d" italic_re a_c_re, i);
		printf(a_c_b "| %s\n" a_c_re, namedLibFuncs[i]);
	}
	printf("\n");

}


























