#include <stdio.h>
#include <assert.h>
#include "operands.h"

#define TRUE  1
#define FALSE 0			

incomplete_jump* ij_head 	= (incomplete_jump*) 0;
unsigned int ij_total 		= 0;
unsigned int ij_size  		= 0;
unsigned int currQuadNo 	= 0;

#define EXPAND_SIZE_IJ 		1024
#define CURR_SIZE_IJ		(ij_total * sizeof(incomplete_jump))
#define NEW_SIZE_IJ 		(EXPAND_SIZE_IJ * sizeof(incomplete_jump) + CURR_SIZE_IJ)


void make_operand 			(expr* e, vmarg* arg){

	if(e == NULL){
		arg->val = -1;
		arg->type = -1;
		return ;

	}

	switch(e->type){

		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case assignexpr_e:
		case newtable_e:		{
									assert(e->sym);
									arg->val 	= e->sym->offset;

									switch(e->sym->space){
										
										case programVar:	arg->type = global_a; break;
										case functionLocal:	arg->type = local_a; break;
										case formalArg:		arg->type = formal_a; break;
										default: assert(0);

									}
									break;
								}

		case constbool_e: 		{
									if(e->boolConst == '0')
										arg->val = 0;
									else
										arg->val = 1;

									arg->type 	= bool_a;
									break;
						  		}

		case conststring_e:		{
									arg->val 	= INSERTER_STRING(e->strConst);
									arg->type 	= string_a;
									break;
							 	}

		case constnum_e:		{
									
									arg->val 	= INSERTER_NUM(e->numConst);
									arg->type 	= number_a;
									break;
								}

		case nil_e:				{
									arg->type 	= nil_a; break;
								}

		case programfunc_e: 	{
									arg->type 	= userfunc_a;
									arg->val 	= INSERTER_USERFUNC(e->sym->value.funcVal->taddress, e->sym->value.funcVal->totallocals,e->sym->value.funcVal->totalargs, (char*) e->sym->value.funcVal->name);
									break;
								}

		case libraryfunc_e:		{
									arg->type 	= libfunc_a;
									arg->val 	= INSERTER_LIBFUNC((char*) e->sym->value.funcVal->name);
									break;
								}

		default :					assert(0);

	}

}

void make_numberOperand 	(vmarg *arg, double val){

	arg->val = INSERTER_NUM(val);
	arg->type = number_a;

}

void make_boolOperand 		(vmarg* arg, unsigned int val){

	arg->val = val;
	arg->type = bool_a;

}

void make_retvalOperand 	(vmarg *arg){

	arg->type = retval_a;

}

// GENERETOR
void generate 				(vmopcode op, quad *quadInput){

	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	op;
	t.srcLine 		= 	nextinstructionlabel();

	make_operand(quadInput->arg1, 	&t.arg1);
	make_operand(quadInput->arg2, 	&t.arg2);
	make_operand(quadInput->result, &t.result);
	quadInput->taddress = nextinstructionlabel(); 
	
	emitInstr(t);

}

void generate_ADD 			(quad *quadInput){ generate(add_v, quadInput); }
void generate_SUB 			(quad *quadInput){ generate(sub_v, quadInput); }
void generate_MUL 			(quad *quadInput){ generate(mul_v, quadInput); }
void generate_DIV 			(quad *quadInput){ generate(div_v, quadInput); }
void generate_MOD 			(quad *quadInput){ generate(mod_v, quadInput); }
void generate_NEWTABLE 		(quad *quadInput){ generate(newtable_v, quadInput); }
void generate_TABLEGETELM 	(quad *quadInput){ generate(tablegetelem_v, quadInput); }
void generate_TABLESETELEM	(quad *quadInput){ generate(tablesetelem_v, quadInput); }
void generate_ASSIGN 		(quad *quadInput){ generate(assign_v, quadInput); }

void generate_NOP 			(quad *quadInput){

	instruction t; 
	setArgsNull(&t);
	t.opcode 		=	nop_v; 
	t.srcLine 		= 	nextinstructionlabel();
	quadInput->taddress = nextinstructionlabel();


	emitInstr(t); 
} //arg unused

// GENERETOR RELATIONALATOR
void generate_relational(vmopcode op, quad *quadInput){

	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	op;
	t.srcLine 		= 	nextinstructionlabel();
	
	make_operand(quadInput->arg1, &t.arg1);
	make_operand(quadInput->arg2, &t.arg2);

	t.result.type = label_a;

	if((int)quadInput->result->numConst < currprocessedquad())
		t.result.val = quads[(int)quadInput->result->numConst].taddress; 
	else
		add_incomplete_jump(nextinstructionlabel(), quadInput->result->numConst);

	quadInput->taddress = nextinstructionlabel(); 
	emitInstr(t);

}

void generate_JUMP 			(quad *quadInput){ generate_relational(jump_v,	quadInput); }
void generate_IF_EQ 		(quad *quadInput){ generate_relational(jeq_v,	quadInput); }
void generate_IF_NOTEQ 		(quad *quadInput){ generate_relational(jne_v, 	quadInput); }
void generate_IF_GREATER 	(quad *quadInput){ generate_relational(jgt_v, 	quadInput); }
void generate_IF_GREATEREQ 	(quad *quadInput){ generate_relational(jge_v, 	quadInput); }
void generate_IF_LESS 		(quad *quadInput){ generate_relational(jlt_v, 	quadInput); }
void generate_IF_LESSEQ 	(quad *quadInput){ generate_relational(jle_v, 	quadInput); }

void generate_PARAM(quad *quadInput) {

	quadInput->taddress = nextinstructionlabel();
	instruction t;
	setArgsNull(&t);
	t.opcode  		= 	pusharg_v;
	t.srcLine  		= 	nextinstructionlabel();

	make_operand(quadInput->result, &t.result);
	emitInstr(t);

}

void generate_CALL(quad *quadInput) {

	quadInput->taddress = nextinstructionlabel(); 
	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	call_v; 
	t.srcLine 		= 	nextinstructionlabel();

	make_operand(quadInput->result, &t.result);
	emitInstr(t);

}

void generate_GETRETVAL(quad *quadInput) { 

	quadInput->taddress = nextinstructionlabel(); 
	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	assign_v; 
	t.srcLine 		= 	nextinstructionlabel();
		
	make_operand(quadInput->result, &t.result); 
	make_retvalOperand(&t.arg1);
	emitInstr(t);

}

void generate_FUNCSTART(quad *quadInput) { 

	SymTableEntry f = quadInput->result->sym;
	f->value.funcVal->taddress = nextinstructionlabel();
	quadInput->taddress = nextinstructionlabel();

	pushFuncStackTarget(f);

	SymTableEntry s = topFuncStackTarget();

	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	funcenter_v; 
	t.srcLine 		= 	nextinstructionlabel();

	make_operand(quadInput->result, &t.result);
	emitInstr(t);

}

void generate_RETURN(quad *quadInput) { 

	quadInput->taddress = nextinstructionlabel();
	instruction t;
	setArgsNull(&t);
	t.opcode 		= 	assign_v;
	t.srcLine 		= 	nextinstructionlabel();

	make_retvalOperand(&t.result);
	make_operand(quadInput->result,&t.arg1);
	emitInstr(t);

	SymTableEntry f = topFuncStackTarget();
	appendFuncStackTarget(f, nextinstructionlabel());
	assert(f->value.funcVal->returnList);

	setArgsNull(&t);
	t.srcLine = nextinstructionlabel();
	t.opcode = jump_v;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	emitInstr(t);

}

void generate_FUNCEND(quad *quadInput) {

 	SymTableEntry f = popFuncStackTarget();
 	//Backpatch return list
 	returnList* reader = f->value.funcVal->returnList;

 	while(reader != NULL){
 		patchInstrLabel(reader->instrLabel,nextinstructionlabel());
 		reader = reader->next;
 	}

 	quadInput->taddress = nextinstructionlabel();
 	instruction t;
 	setArgsNull(&t);
 	t.opcode 		= 	funcexit_v;
 	t.srcLine 		= 	nextinstructionlabel();
		
 	make_operand(quadInput->result, &t.result);
 	emitInstr(t);

 }

// GENERATIONAL FUNCTIONS

void patchInstrLabel(unsigned int instrNo, unsigned int taddress){
	instructions[instrNo].result.val = taddress;
}

void patchIncompleteJumps(unsigned int totalQuads){

	int i = 0;

	for(; i < ij_total; i++){
		if(ij_head[i].iaddress == totalQuads){
			patchInstrLabel(ij_head[i].instrNo,totalInstructions);
		}else{
			patchInstrLabel(ij_head[i].instrNo, quads[ij_head[i].iaddress].taddress);
		}
	}

}

unsigned int nextinstructionlabel(){ return totalInstructions; }

void EXPANDER_IJ(void){

	assert(ij_size == ij_total);
	incomplete_jump* p = (incomplete_jump*) malloc (NEW_SIZE_IJ);
	if(ij_head){
		memcpy(p, ij_head, CURR_SIZE_IJ);
		free(ij_head);
	}
	ij_head = p;
	ij_size += EXPAND_SIZE_IJ;

}

void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress){ 

	if(ij_total == ij_size)
		EXPANDER_IJ();

	incomplete_jump* p = ij_head + ij_total++;

	p -> instrNo	= 	instrNo;
	p -> iaddress	= 	iaddress;

}

unsigned int currprocessedquad(void){ return currQuadNo; }

void reset_operand(vmarg *arg){ arg->val = -1 ; }

void setArgsNull(instruction* t){

	t->arg1.val		=	-1; t->arg1.type	= 	11;
	t->arg2.val		=	-1; t->arg2.type 	= 	11;
	t->result.val	=	-1; t->result.type 	=	11; 

}

generator_func_t generators[] = {

	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_JUMP,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELM,
	generate_TABLESETELEM,
	generate_GETRETVAL,
	generate_NOP,
	generate_RETURN

};

void generateTcode(unsigned int totalQuads){

	int i = 0;
	for(; i<totalQuads; ++i){
		//printf("quads[%d].op : %d\n",i,quads[i].op );
		currQuadNo = i;

		(*generators[quads[i].op])(quads+i);
	}

	patchIncompleteJumps(totalQuads);

	
	//PRINTER_STR();printf("\n");
	//PRINTER_NUM();printf("\n");
	//PRINTER_USERFUNC();printf("\n");
	//PRINTER_LIB();printf("\n");

}









