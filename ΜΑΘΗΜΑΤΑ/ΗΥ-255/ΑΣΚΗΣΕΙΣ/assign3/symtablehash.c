/*MARANTOS
ALEXANDROS 3329
3H SEIRA ASKISEON
HY 255		*/

#include "symtable.h"

#define HASH_MULTI 65599

struct SymTable
{
	unsigned int sum;
	SymT hasharray[NUM_BUCKETS];
};

struct Sym
{
	char *key;
	int *value;
	struct Sym *next;
};

/*my hash function*/
static unsigned int SymTable_hash(const char *pcKey)
{
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTI + pcKey[ui];

	return uiHash % NUM_BUCKETS;
}

/*mallocs new symtable node and returns it*/
SymTable_T SymTable_new(void)
{
	SymT newsym;
	SymTable_T newarr;
	int i;

	newsym = malloc(sizeof(struct Sym));
	assert(newsym != NULL);

	newarr = malloc(sizeof(SymTable_T));
	assert(newarr != NULL);

	newsym->key = NULL;
	newsym->value = NULL;

	newarr->sum = 0;
	/*eisagogi ton nodes ston hash table*/
	for (i = 0; i < NUM_BUCKETS; i++)
	{
		newarr->hasharray[i] = newsym;
	}

	return newarr;
}

/*checks if osymtable contains 1 binding with pckey*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
	int i;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	for (i = 0; i < NUM_BUCKETS; i++)
	{
		if (oSymTable->hasharray[i]->key == pcKey)
		{
			return 1;
		}
	}
	return 0;
}

/*adds a node containing pckey, if it's there does nothing*/
int SymTable_put(SymTable_T oSymTable, char *pcKey, void *pvValue)
{
	SymT newn;
	unsigned int res;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(pvValue != NULL);

	if (SymTable_contains(oSymTable, pcKey) == 0) /*no bindings*/
	{
		newn = malloc(sizeof(struct Sym));
		if (newn == NULL)
		{
			return 0;
		}

		res = SymTable_hash(pcKey);
		heads = oSymTable->hasharray[res];

		newn->key = malloc((strlen(pcKey) + 1) * sizeof(char));
		strcpy(newn->key, pcKey); /*save key*/
		newn->value = pvValue;

		heads = newn;
		oSymTable->sum++;
		oSymTable->hasharray[res] = heads;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*returns the number of bindings of osymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
	assert(oSymTable != NULL);

	return (oSymTable->sum);
}

/*finds the node with pckey and removes it*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
	SymT previous = NULL;
	SymT help;
	unsigned int res;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	if (SymTable_contains(oSymTable, pcKey) == 0) /*no bindings*/
	{
		return 0;
	}
	else
	{
		res = SymTable_hash(pcKey);
		help = oSymTable->hasharray[res];
		while (help != NULL)
		{
			if (help->key == pcKey)
			{
				break;
			}
			previous = help;
			help = help->next;
		}

		if (previous != NULL)
		{
			return 0;
		}
		else
		{
			previous->next = help->next;
			free(help);
		}
		oSymTable->sum--;
		return 1;
	}
}

/*ckecks if there is binding with pckey and returns it*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
	unsigned int res;
	SymT help;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	res = SymTable_hash(pcKey);

	help = oSymTable->hasharray[res];
	while (help != NULL)
	{
		if (help->key == pcKey)
		{
			return help->key;
		}

		help = help->next;
	}

	return NULL;
}

void SymTable_free(SymTable_T oSymTable)
{
	SymT help;
	SymT helpsym;
	int i;

	if (oSymTable == NULL)
	{
		return; /*do nothing*/
	}

	for (i = 0; i < NUM_BUCKETS; i++)
	{
		help = oSymTable->hasharray[i];
		while (help != NULL)
		{
			helpsym = help->next;
			free(help->key);
			free(help);
			help = helpsym;
		}
	}
	free(oSymTable);
}

/*pfAplly in every binding with the extra*/
void SymTable_map(SymTable_T oSymTable,
				  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
				  void *pvExtra)
{
	SymT help;
	int i;

	assert(oSymTable != NULL);
	assert(pfApply != NULL);

	for (i = 0; i < NUM_BUCKETS; i++)
	{
		help = oSymTable->hasharray[i];
		while (help != NULL)
		{
			(*pfApply)(help->key, help->value, pvExtra);

			help = help->next;
		}
	}
}