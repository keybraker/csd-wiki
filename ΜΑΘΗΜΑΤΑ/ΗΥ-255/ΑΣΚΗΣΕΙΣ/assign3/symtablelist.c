/*MARANTOS
ALEXANDROS 3329
3H SEIRA ASKISEON
HY 255		*/

#include "symtable.h"

struct SymTable
{
	char *key;
	int *value;
	struct SymTable *next;
};

/*mallocs new symtable node and returns it*/
SymTable_T SymTable_new(void)
{
	SymTable_T newsym;

	newsym = malloc(sizeof(struct SymTable));

	assert(newsym != NULL);

	newsym->key = NULL;
	newsym->value = NULL;
	newsym->next = NULL;

	head = newsym;

	return newsym;
}

/*frees whole memory osymtable uses, if osymtable = null do nothing*/
void SymTable_free(SymTable_T oSymTable)
{
	if (oSymTable == NULL)
	{
		printf("empty array do not free memory\n");
		return;
	}
	else
	{
		free(oSymTable);
	}
}

/*returns the number of bindings of osymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
	unsigned int counter = 0;
	SymTable_T head_o;

	assert(oSymTable != NULL);

	head_o = oSymTable;
	while (head_o != NULL)
	{
		counter++;
		head_o = head_o->next;
	}
	return counter;
}

/*adds a node containing pckey, if it's there does nothing*/
int SymTable_put(SymTable_T oSymTable, char *pcKey, void *pvValue)
{
	SymTable_T head_o = NULL;
	SymTable_T newsym = NULL;
	int flag = 0;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	head_o = oSymTable;

	while (head_o != NULL)
	{
		if (head_o->key == pcKey)
		{
			flag = 1;
		}
		head_o = head_o->next;
	}

	if (flag == 0)
	{
		newsym = malloc(sizeof(struct SymTable));

		newsym->key = pcKey;
		newsym->value = pvValue;
		newsym->next = oSymTable;

		oSymTable = newsym;
		head = oSymTable;

		return 1;
	}

	return 0;
}

/*finds the node with pckey and removes it*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
	SymTable_T head_o;
	SymTable_T previous;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	head_o = oSymTable;
	previous = NULL;
	while (head_o != NULL)
	{
		if (head_o->key == pcKey)
		{
			if (head_o->next == NULL)
			{
				/*teleutaio node tis listas*/
				if (previous == NULL)
				{
					oSymTable = NULL; /*adeia lista pleon*/
					head = NULL;
					return 1;
				}
				else
				{
					previous->next = NULL;
					return 1;
				}
			}
			else
			{
				if (previous == NULL)
				{
					/*proto node tis listas*/
					oSymTable = head_o->next;
					head = oSymTable;
					return 1;
				}
				else
				{
					previous->next = head_o->next; /*to prospernao*/
					return 1;
				}
			}
		}

		previous = head_o;
		head_o = head_o->next;
	}

	/*an ftasei edo den brike to pckey */
	return 0;
}

/*checks if osymtable contains 1 binding with pckey*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
	SymTable_T head_o;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	head_o = oSymTable;

	while (head_o != NULL)
	{
		if (head_o->key == pcKey)
		{
			return 1;
		}
		head_o = head_o->next;
	}

	return 0;
}

/*ckecks if there is binding with pckey and returns it*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
	SymTable_T head_o;

	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	head_o = oSymTable;

	while (head_o != NULL)
	{
		if (head_o->key == pcKey)
		{
			return head_o;
		}

		head_o = head_o->next;
	}
	return NULL;
}

/*pfAplly in every binding with the extra*/
void SymTable_map(SymTable_T oSymTable,
				  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
				  void *pvExtra)
{
	SymTable_T node;

	assert(oSymTable != NULL);
	assert(pfApply != NULL);
	assert(pvExtra != NULL);

	for (node = head;
		 node != NULL;
		 node = node->next)
	{
		(*pfApply)(node->key, node->value, pvExtra);
	}
}