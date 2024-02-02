#include "ConstTablesLinker.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define a_c_r "\x1b[31m"
#define a_c_y "\x1b[33m"
#define a_c_re "\x1b[0m"

typedef enum avm_memcell_t avm_memcell_t;
typedef struct avm_memcell avm_memcell;
typedef struct avm_table avm_table;
typedef struct avm_table_bucket avm_table_bucket;

unsigned int totalActuals;

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

enum avm_memcell_t
{

	number_m = 0,
	string_m = 1,
	bool_m = 2,
	table_m = 3,
	userfunc_m = 4,
	libfunc_m = 5,
	nil_m = 6,
	undef_m = 7

};

struct avm_memcell
{

	avm_memcell_t type;

	union
	{

		double numVal;
		char *strVal;
		unsigned char boolVal;
		avm_table *tableVal;
		unsigned int funcVal;
		char *libfuncVal;

	} data;
};

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m));

avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void)
{

	unsigned int i = 0;

	for (i = 0; i < AVM_STACKSIZE; i++)
	{
		AVM_WIPEOUT(stack[i]);
		stack[i].type = undef_m;
	}
}

#define AVM_TABLE_HASHSIZE 211

struct avm_table_bucket
{

	avm_memcell key;
	avm_memcell value;
	avm_table_bucket *next;
};

struct avm_table
{

	unsigned int refCounter;
	avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
	unsigned int total;
};

avm_table *avm_tableNew(void);
void avm_tableDestroy(avm_table *t);
avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index);
void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *value);
void avm_tableIncRefCounter(avm_table *t);
void avm_tableDecRefCounter(avm_table *t);
void avm_tableBucketsInit(avm_table_bucket **p);
void avm_memcellClear(avm_memcell *m);
void avm_tableBucketsDestroy(avm_table_bucket **m);

typedef void (*memclear_func_t)(avm_memcell *);

extern void memclear_string(avm_memcell *m);
extern void memclear_table(avm_memcell *m);

extern void avm_warning(char *msg1, char *id, char *msg2);
extern void avm_assign(avm_memcell *lv, avm_memcell *rv);

extern void avm_error(char *msg1, char *id, char *msg2);
extern char *avm_tostring(avm_memcell *m);
extern void avm_callLibFunc(char *libfuncName);
extern void avm_callSaveEnvironment(void);

extern void avm_dec_top(void);
extern void avm_push_envValue(unsigned int val);

extern userfunc *avm_getfuncinfo(unsigned int address);
extern unsigned int avm_get_envvalue(unsigned int i);

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char *id);

unsigned int avm_totalactuals(void);

avm_memcell *avm_getactual(unsigned int i);
void libfunc_print(void);
void avm_registerlibfunc(char *id, library_func_t addr);

void printTable(avm_memcell *t);

typedef char *(*tostring_func_t)(avm_memcell *);

extern char *number_tostring(avm_memcell *);
extern char *string_tostring(avm_memcell *);
extern char *bool_tostring(avm_memcell *);
extern char *table_tostring(avm_memcell *);
extern char *userfunc_tostring(avm_memcell *);
extern char *libfunc_tostring(avm_memcell *);
extern char *nil_tostring(avm_memcell *);
extern char *undef_tostring(avm_memcell *);

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

typedef unsigned char (*cmp_func_t)(double x, double y);

unsigned char jle_impl(double x, double y);
unsigned char jge_impl(double x, double y);
unsigned char jlt_impl(double x, double y);
unsigned char jgt_impl(double x, double y);

typedef unsigned char (*tobool_func_t)(avm_memcell *);

unsigned char number_tobool(avm_memcell *m);
unsigned char string_tobool(avm_memcell *m);
unsigned char bool_tobool(avm_memcell *m);
unsigned char table_tobool(avm_memcell *m);
unsigned char userfunc_tobool(avm_memcell *m);
unsigned char libfunc_tobool(avm_memcell *m);
unsigned char nil_tobool(avm_memcell *m);
unsigned char undef_tobool(avm_memcell *m);

unsigned char avm_tobool(avm_memcell *m);

void libfunc_typeof(void);

void avm_initialize(void);
void libfunc_totalarguments(void);
