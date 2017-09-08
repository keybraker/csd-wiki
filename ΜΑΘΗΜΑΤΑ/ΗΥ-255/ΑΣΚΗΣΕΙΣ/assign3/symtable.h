/*MARANTOS
ALEXANDROS 3329
3H SEIRA ASKISEON
HY 255		*/

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NUM_BUCKETS 509

struct SymTable *head;
struct Sym *heads;

typedef struct SymTable *SymTable_T;

typedef struct Sym *SymT;

void pfApply(const char *pcKey, void *pvValue, void *pvExtra) {

	*(int *) pvValue += *(int *) pvExtra;

}
/*returns a new symtable_t which is empty*/
SymTable_T SymTable_new(void);

/*frees whole memory osymtable uses, if osymtable = null do nothing*/
void SymTable_free(SymTable_T oSymTable);

/*returns the number of bindings of osymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable);

/**/
int SymTable_put(SymTable_T oSymTable, char *pcKey, void *pvValue);

int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

void* SymTable_get(SymTable_T oSymTable, const char *pcKey);

void SymTable_map(SymTable_T oSymTable,
      void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
      void *pvExtra);
