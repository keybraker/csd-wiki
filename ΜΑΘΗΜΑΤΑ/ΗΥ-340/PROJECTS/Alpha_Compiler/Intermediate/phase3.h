#include "../bison/bison_libs/DataStruct.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

typedef enum iopcode iopcode;
typedef enum expr_t expr_t;
typedef struct expr expr;
typedef struct method_call method_call;
typedef struct quad quad;
typedef enum symbol_t symbol_t;
typedef struct symbol symbol;
typedef struct myStack myStack;

typedef struct loopStack loopStack;
typedef struct BClist BClist;

typedef struct logicList logicList;

quad *quads;
unsigned int total;
unsigned int currQuad;

unsigned int programVarOffset;
unsigned int functionLocalOffset;
unsigned int formalArgOffset;
unsigned int scopeSpaceCounter;

int mustDecrease;
int mustIncrease;

enum iopcode
{

	ASSIGN,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	jump,
	if_eq,
	if_noteq,
	if_lesseq,
	if_greatereq,
	if_less,
	if_greater,
	call,
	param,
	funcstart,
	funcend,
	tablecreate,
	tablegetelem,
	tablesetelem,
	getretval,
	no_op,
	ret

};

enum expr_t
{

	var_e,
	tableitem_e,

	programfunc_e,
	libraryfunc_e,

	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,

	constnum_e,
	constbool_e,
	conststring_e,

	nil_e

};

struct forLoopStruct
{

	int test;
	int enter;
};

struct expr
{

	expr_t type;
	SymTableEntry sym;
	expr *index;
	expr *indexedVal;
	double numConst;
	char *strConst;
	unsigned char boolConst;
	expr *next;
	expr *prev;

	logicList *truelist;
	logicList *falselist;
	int cameFromNot;
	int voidParam;
};

struct logicList
{

	int QuadNo;
	logicList *next;
};

struct method_call
{

	expr *elist;
	int method;
	char *name;
};

struct quad
{

	iopcode op;
	expr *result;
	expr *arg1;
	expr *arg2;
	unsigned int label;
	unsigned int line;
	unsigned int taddress;
};

myStack *functionLocalsStack;
myStack *loopCounterStack;
myStack *functionJumpStack;

struct myStack
{

	int info;
	myStack *next;
};

struct loopStack
{

	BClist *breaklist;
	BClist *contlist;
	loopStack *next;
};

struct BClist
{

	int QuadNo;
	BClist *next;
};

void emit();
char *newTempName();
SymTableEntry newTemp(int scope);
void resetTemp();
scopespace_t currScopeSpace(void);
unsigned int currScopeOffset(void);
void inCurrScopeOffset(void);
void enterScopeSpace(void);
void exitScopeSpace(void);
void initializePhaseThree(void);
void resetFormalArgOffset(void);
void resetFunctionLocalOffset(void);
void restoreCurrScopeOffset(unsigned int n);
void patchLabel(unsigned int quadno, unsigned int label);
int nextQuadLabel(void);
void checkUminus(expr *e);
expr *newexpr(expr_t);
expr *newexpr_constString(char *s);
expr *newexpr_constNumber(double d);
expr *newexpr_constBool(unsigned char c);
expr *newexpr_Nil();
expr *lvalue_expr(SymTableEntry sym);
expr *emit_iftableitem(expr *e, int quadno, int line, int scope);
expr *member_item(expr *lvalue, int quadno, int line, int scope, char *name);
expr *make_call(expr *lvalue, expr *elist, int scope, int line);

// <Meriki apotimisi !>

logicList *makelist(int quadno);
logicList *mergeLocicLists(logicList *list1, logicList *list2);
void backPatchList(logicList *list, int quadno);
void checkForEmitAND(expr *e, int line, int reloppassed);
void checkForEmitOR(expr *e, int line, int reloppassed);
void checkForEmitNotEq(expr *e, int line, int scope);
void checkForEmitEqEq(expr *e, int line, int scope);

// </End Meriki apotimisi !>

int isStackEmpty();
void push(int mem);
int pop();
int isLoopCounterStackEmpty();
void pushLoopCounter(int mem);
int popLoopCounter();

int isFuncJumpStackEmpty();
void pushFuncJump(int mem);
int popFuncJump();

// gia ta break kai cont
loopStack *loopTop;
int isLoopStackEmpty();
int isBreakListEmpty();
int isContListEmpty();
void loopPush();
void breakPush(int QuadNo);
void contPush(int QuadNo);
loopStack *loopPop();