#include "phase3.h"

int tempcounter = 0;
int numberDigitsTemp(int tempcounter);

void initializePhaseThree(void){

	quad *quads = (quad*) 0;
	total = 0;
	currQuad = 0;

	programVarOffset = 0;
	functionLocalOffset = 0;
	formalArgOffset = 0;
	scopeSpaceCounter = 1;
	
	myStack *functionLocalsStack = NULL;
	myStack *functionJumpStack = NULL;
	
}

int nextQuadLabel(void) { return currQuad; }

void expand (void) {
	assert(total == currQuad);
	quad* p = (quad*) malloc(NEW_SIZE);
	if(quads){
		memcpy(p, quads, CURR_SIZE);
		free(quads);
	} 
	quads = p;
	total += EXPAND_SIZE;
}

void emit (

		iopcode			op,
		expr* 			arg1,
		expr* 			arg2,
		expr*			result,
		unsigned int 	label,
		unsigned int 	line

	) {

	if (currQuad == total)
		expand(); 

	quad* p 			= quads+currQuad++;
	p->op 				= op;
	p->arg1				= arg1;
	p->arg2				= arg2;
	p->result			= result;
	p->label 			= label;
	p->line				= line;

}

char *newTempName(){

	const char *prefix = "_t";
    char *tempName = NULL;
    const int prefix_size = strlen(prefix) + 1;

    tempName = (char *) malloc(sizeof(prefix_size + numberDigitsTemp(tempcounter)));
    sprintf(tempName,"_t%d",tempcounter);

    tempcounter++;

    return tempName;
}

void resetTemp() { tempcounter = 0; }

SymTableEntry newTemp(int scope) {

	char *name = newTempName();
	SymTableEntry sym = NULL;

	sym = lookUpTemp(name,scope);

	if( sym == NULL ){
		if(scope == 0)
			sym	= insert(name, variable, GLOBAL, scope, -1,0, currScopeSpace(), currScopeOffset()); // !!! PREPEI NA EXOUN OFFSET
		else
			sym	= insert(name, variable, LOCAL, scope, -1,0, currScopeSpace(), currScopeOffset()); 
		inCurrScopeOffset();
		return sym;
	}else{
		return  sym;
	}
}

int numberDigitsTemp(int tempcounter){

	int counter = 0;

    if(tempcounter == 0)
        return 1;

    while(tempcounter != 0){
        tempcounter /= 10;
        counter++;
    }

    return counter;

}


scopespace_t currScopeSpace(void){
	if(scopeSpaceCounter == 1)
		return programVar;
	else if(scopeSpaceCounter % 2 == 0)
		return formalArg;
	else
		return functionLocal;
}

unsigned int currScopeOffset(void){
	switch(currScopeSpace()){
		case programVar		: return programVarOffset;
		case functionLocal	: return functionLocalOffset;
		case formalArg		: return formalArgOffset;
		default				: assert(0);
	}
}

void inCurrScopeOffset(void){
	switch(currScopeSpace()){
		case programVar 	: ++programVarOffset; break;
		case functionLocal  : ++functionLocalOffset; break;
		case formalArg 		: ++formalArgOffset; break;
		default 			: assert(0);
	}
}

void enterScopeSpace(void){
	++scopeSpaceCounter;
}

void exitScopeSpace(void){
	assert(scopeSpaceCounter > 1);
	--scopeSpaceCounter;
}

void patchLabel(unsigned int quadno,unsigned int label){
	assert(quadno < currQuad);
	quads[quadno].result =  newexpr_constNumber(label);
}

expr* newexpr(expr_t t){
	expr* e = (expr*) malloc(sizeof(expr));
	memset(e,0,sizeof(expr));
	e->type = t;
	return e;
}

expr* newexpr_constString(char *s){
	expr* e = newexpr(conststring_e);
	e->strConst = strdup(s);
	return e;
}

expr* newexpr_constNumber(double d){
	expr* e = newexpr(constnum_e);
	e->numConst = d;
	return e;
}

expr* newexpr_constBool(unsigned char c){
	expr *e = newexpr(constbool_e);
	e->boolConst = c;
	return e;
}

expr* newexpr_Nil(){
	expr* e = newexpr(nil_e);
	e->numConst = 0;
	return e;
}

void checkUminus(expr *e){

	if(e->type == constbool_e 		|| \
		e->type == conststring_e 	|| \
		e->type == nil_e 			|| \
		e->type == newtable_e 		|| \
		e->type == programfunc_e 	|| \
		e->type == libraryfunc_e 	|| \
		e->type == boolexpr_e){
		printf(a_c_r "Illegal expression unary minus!\n" a_c_re);
		exit(0);
	}

}

expr* lvalue_expr(SymTableEntry sym){

	assert(sym);

	expr* e = (expr*) malloc (sizeof(expr));
	memset(e,0,sizeof(expr));

	e->next = (expr*) 0;
	e->sym = sym;

	switch(sym->type){
		case LOCAL 		: e->type = var_e; 			break;
		case GLOBAL 	: e->type = var_e; 			break;
		case FORMAL 	: e->type = var_e; 			break;
		case LIBFUNC 	: e->type = libraryfunc_e; 	break;
		case USERFUNC 	: e->type = programfunc_e; 	break;
		default 		: assert(0);
	}

	return e;

}

expr* emit_iftableitem(expr* e,int quadno,int line,int scope){

	if(e->type != tableitem_e)
		return e;
	else{
		expr* result = newexpr(var_e);
		result->sym = newTemp(scope);
		emit(tablegetelem,e,e->index,result,quadno,line);
		return result;
	}
}

expr* member_item(expr* lvalue, int quadno, int line, int scope, char* name){

	lvalue 		= 	emit_iftableitem(lvalue,quadno,line,scope);
	expr* item 	= 	newexpr(tableitem_e);
	item->sym	= 	lvalue->sym;
	item->index	=	newexpr_constString(name);
	return item;

}

void resetFormalArgOffset(){
	formalArgOffset = 0;
}

void resetFunctionLocalOffset(){
	functionLocalOffset = 0;
}

expr* make_call(expr* lvalue, expr* elist, int scope, int line){

    expr* func = emit_iftableitem(lvalue,nextQuadLabel(),line,scope);
    expr* tmp = elist;

    //gia na pao sto telos (exo balei pleon pedio "prev" sto struct expr)
    while(tmp->next!=NULL){
        tmp = tmp->next;
    }

    if(elist->voidParam == 0){

    	while(tmp!=NULL){
        	emit(param,NULL,NULL,tmp,nextQuadLabel(),line);
        	tmp = tmp->prev;
    	}

    }
   
    emit(call,NULL,NULL,func,nextQuadLabel(),line);
    expr* result = newexpr(var_e);
    result->sym  = newTemp(scope);
    emit(getretval,NULL,NULL,result,nextQuadLabel(),line);
    return result;

}

logicList* makelist(int quadno){

	logicList* list = (logicList*) malloc(sizeof(logicList));
	memset(list,0,sizeof(logicList));
	list->QuadNo = quadno;
	list->next = NULL;
	return list;

}

logicList* mergeLocicLists(logicList* list1, logicList* list2){

	logicList* tmp = NULL;

	if(list1 == NULL && list2 == NULL){
		return NULL;
	}
	else if(list1 == NULL && list2 != NULL){
		return list2;
	}else if(list1 != NULL && list2 == NULL){
		return list1;
	}else{
		tmp = list1;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = list2;
		return list1;
	}

	assert(0);

}

void backPatchList(logicList* list, int quadno){

	logicList* tmp = list;

	while(tmp != NULL){
		patchLabel(tmp->QuadNo,quadno);
		tmp = tmp->next;
	}

}

void checkForEmitAND(expr* e,int line, int not_rule_passed){

	if(e->type != boolexpr_e){

		e->truelist   = makelist(nextQuadLabel());
        e->falselist  = makelist(nextQuadLabel()+1);
        emit(if_eq,newexpr_constBool('1'),e,NULL,nextQuadLabel(),line);
        emit(jump,NULL,NULL,NULL,nextQuadLabel(),line);

        backPatchList(e->truelist,nextQuadLabel());
        
	}
	
}

void checkForEmitOR(expr* e, int line, int not_rule_passed){

	if(e->type != boolexpr_e){

		e->truelist   = makelist(nextQuadLabel());
        e->falselist  = makelist(nextQuadLabel()+1);
        emit(if_eq,newexpr_constBool('1'),e,NULL,nextQuadLabel(),line);
        emit(jump,NULL,NULL,NULL,nextQuadLabel(),line);

        backPatchList(e->falselist,nextQuadLabel());
	
	}

}

void checkForEmitNotEq(expr* e, int line, int scope){

	if(e->type == boolexpr_e && e->cameFromNot == 1){

        e->sym = newTemp(scope);
        backPatchList(e->truelist,nextQuadLabel());
        emit(ASSIGN,newexpr_constBool('1'),NULL,e,nextQuadLabel(),line);
        emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),line);
        backPatchList(e->falselist,nextQuadLabel());
        emit(ASSIGN,newexpr_constBool('0'),NULL,e,nextQuadLabel(),line);
   
    }

}

void checkForEmitEqEq(expr* e, int line, int scope){

	if(e->type == boolexpr_e && e->cameFromNot == 1){

        e->sym = newTemp(scope);
        backPatchList(e->truelist,nextQuadLabel());
        emit(ASSIGN,newexpr_constBool('1'),NULL,e,nextQuadLabel(),line);
        emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),line);
        backPatchList(e->falselist,nextQuadLabel());
        emit(ASSIGN,newexpr_constBool('0'),NULL,e,nextQuadLabel(),line);
   
    }

}


