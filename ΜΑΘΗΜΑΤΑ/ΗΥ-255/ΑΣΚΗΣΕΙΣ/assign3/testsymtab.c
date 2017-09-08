/*MARANTOS
ALEXANDROS 3329
3H SEIRA ASKISEON
HY 255		*/

#include "symtable.h"


int main()
{
	unsigned int k;
	int l,m,n;
	char pcKey[5] = "alexi";
	char Key[5] = "aleko";

	void *pvValue;
	void *pvExtra;

	SymTable_T keybind = NULL;

	head = SymTable_new();
	printf("ekana new\n");	
	
	k = SymTable_getLength(head);
	printf("h length epistrefei: %u\n", k);

	l = SymTable_put(head, pcKey, pvValue);
	printf("h put epistrefei: %d\n", l);
	
	l = SymTable_put(head, Key, pvValue);
	printf("h put epistrefei: %d\n", l);
	
	n = SymTable_contains(head, pcKey);
	printf("h contains epistrefei: %d\n", n);
	
	keybind = SymTable_get(head, pcKey);
	if(keybind == NULL)
	{
		printf("einai null\n");
	}
	else
	{
		printf("brika key\n");
	}

	/*SymTable_map(head, (*pfApply)(pcKey, pvValue, pvExtra), pvExtra);*/

	m = SymTable_remove(head, pcKey);
	printf("h remove epistrefei: %d\n", m);

	SymTable_free(head);
	printf("ekana free\n");




	return 0;
}