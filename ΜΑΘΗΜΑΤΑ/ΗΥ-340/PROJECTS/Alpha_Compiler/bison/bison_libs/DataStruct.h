//
//  DataStruct.h
//  dataStruct
//
//  Created by Ioannis Tsiakkas on 21/03/2017.
//  Copyright © 2017 Ioannis Tsiakkas. All rights reserved.
//

#ifndef DataStruct_h
#define DataStruct_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int codeIsCorrect;

#define a_c_r "\x1b[31m"
#define a_c_g "\x1b[32m"
#define a_c_y "\x1b[33m"
#define a_c_b "\x1b[34m"
#define a_c_m "\x1b[35m"
#define a_c_c "\x1b[36m"
#define a_c_re "\x1b[0m"
#define under "\e[4m"
#define under_re "\e[0m"
#define italic "\e[3m"
#define italic_re "\e[0m"
#define bold "\e[1m"
#define bold_re "\e[0m"

#define HASH_SIZE 100
#define MINUS (-1)

#define printVar(readerSS) printf("Name: %s, Scope: %d, line: %d, active: %d, type: %s, union type: %s, offset: %d\n", readerSS->value.varVal->name, readerSS->value.varVal->scope, readerSS->value.varVal->line, readerSS->isActive, SymbolTableTypeStrings[readerSS->type], UnionTypeEnumStrings[readerSS->union_t], readerSS->offset);

#define printFunc(readerSS) printf("Name: %s, Scope: %d, line: %d, active: %d, type: %s, union type: %s, func locals: %d\n", readerSS->value.funcVal->name, readerSS->value.funcVal->scope, readerSS->value.funcVal->line, readerSS->isActive, SymbolTableTypeStrings[readerSS->type], UnionTypeEnumStrings[readerSS->union_t], readerSS->value.funcVal->totallocals);

#define printScopeVar(reader) printf("Name: %s, Scope: %d, line: %d, active: %d, type: %s, union type: %s, offset: %d\n", reader->value.varVal->name, reader->value.varVal->scope, reader->value.varVal->line, reader->isActive, SymbolTableTypeStrings[reader->type], UnionTypeEnumStrings[reader->union_t], reader->offset);

#define printScopeFunc(reader) printf("Name: %s, Scope: %d, line: %d, active: %d, type: %s, union type: %s, func locals: %d\n", reader->value.funcVal->name, reader->value.funcVal->scope, reader->value.funcVal->line, reader->isActive, SymbolTableTypeStrings[reader->type], UnionTypeEnumStrings[reader->union_t], reader->value.funcVal->totallocals);

#define printPointer(reader) printf("%p\n", reader);

typedef struct SymbolTableEntry *SymTableEntry;
typedef struct ScopeStruct *ScopeStruct;
typedef enum SymbolTableType SymbolTableType;
typedef enum UnionTypeEnum unionType;
typedef struct Variable Variable;
typedef struct Function Function;
typedef enum RuleEnum RuleEnum;
typedef struct returnList returnList;

typedef enum scopespace
{
    programVar,
    functionLocal,
    formalArg
} scopespace_t;

enum RuleEnum
{
    AssignExpr,
    Primary,
    Funcdef
};

enum UnionTypeEnum
{
    function,
    variable
};

enum SymbolTableType
{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
};

struct Variable
{

    const char *name;
    unsigned int scope;
    unsigned int line;
};

struct returnList
{

    unsigned int instrLabel;
    returnList *next;
};

struct Function
{

    const char *name;
    unsigned int scope;
    unsigned int line;
    unsigned int totalargs;
    unsigned int iaddress;
    unsigned int totallocals;

    unsigned int taddress;
    returnList *returnList;

    // List of args
};

struct SymbolTableEntry
{

    int isActive;
    SymbolTableType type;
    unionType union_t;

    scopespace_t space;
    unsigned int offset;

    union
    {

        Variable *varVal;
        Function *funcVal;

    } value;

    SymTableEntry nextList;
    SymTableEntry nextScope;
};

struct ScopeStruct
{

    int scope;
    ScopeStruct next;

    SymTableEntry firstScope;
    SymTableEntry lastScope;
};

SymTableEntry BucketList[HASH_SIZE];
SymTableEntry ColisionList[HASH_SIZE];

/* FUNCTION PROTOTYPES */

int notValidAccess(char *name, int scope, int yylineno);
int LookUpGlobalScope(char *name);
int lookUpValidAssignment(char *name, int scope, int yylineno);
int lookUpScopeExistance(char *name, int scope);
int lookUpValidFuncCall(char *name, int scope, int yylineno);
int lookUpScopeRedeclaration(char *name, unionType type, int scope, int yylineno, RuleEnum rule);
SymTableEntry lookUpBucketDuplicate(char *name, int scope);
SymTableEntry lookUpBucketDuplicateLocal(char *name, int scope);
int redeclarationLibFunc(char *name, unionType type, int yylineno);
SymTableEntry LookUpGlobal(char *name, int yylineno);
int changeActivity(int Scope);
int existsInLibFunc(char *name);
SymTableEntry lvalueIsFunction(char *name, int scope);

int formalArgsLibFuncShadow(char *name, int yylineno);
int formalArgsRedeclaration(char *name, int scope, int yylineno);

void libFuncInit();
void initializeArray();
int hashFunction(char *name, int scope);
SymTableEntry newBucket(char *name, enum UnionTypeEnum union_t, SymbolTableType type, int scope, int decLine, scopespace_t scopespace, unsigned int offset);
int scopeConnect(int isFirst, int scope, SymTableEntry newEntry);
SymTableEntry insert(char *name, enum UnionTypeEnum union_t, SymbolTableType type, int scope, int decLine, int fromLocalRule, scopespace_t scopespace, unsigned int offset);
void printWholeStruct();

// PHASE3
SymTableEntry lookUpTemp(char *name, int scope);

// INDISDE PARSER

unsigned int totalGlobals();

#endif /* DataStruct_h */
