#include "cs345sh_header.h"

void unset_func(struct var *root_var)
{
	struct var *reader_var = root_var;
	char *var_name = strtok(strtok(NULL, " "), "\n");
	int guardian = 0;
	if (root_var->name == NULL)
		{ printf("No variable \"%s\" in system memory.\n", var_name); return; }

	while(reader_var != NULL){ 
		if(strcmp(strtok(var_name, "\n"),reader_var->name) == 0)
			{reader_var->data = NULL; guardian=1; break; }
		reader_var = reader_var->next;
	}

	if (guardian == 0){ printf("No variable \"%s\" in system memory.\n", var_name);}
}

