#include "cs345sh_header.h"

void printlvars_func(struct var *root_var)
{
	if (root_var->name == NULL)
	{
		printf("No variables in memory.\n");
	}
	else
	{
		struct var *reader_var = root_var;
		while (reader_var != NULL)
		{
			printf("%s=%s\n", reader_var->name, reader_var->data);
			if (reader_var->data == NULL)
			{
				printf("\n");
			}
			reader_var = reader_var->next;
		}
	}
}
