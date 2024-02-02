#include "cs345sh_header.h"

void echo_func(char *buffer, struct var *root_var)
{
	struct var *reader_var = root_var;
	int i = 0, guardianone = 0;

	while (buffer[i] != '\n')
	{
		if (buffer[i] == '$')
		{
			guardianone = 1;
			break;
		}
		i++;
	}

	if (guardianone == 1)
	{
		while (i >= 0)
		{
			buffer++;
			i--;
		}
	}
	else
	{
		printf("Symbol \"$\" has not been typed.\n");
		return;
	}

	int guardian = 0;
	if (root_var->name == NULL)
	{
		printf("No variable \"%s\" in system memory.\n", buffer);
		return;
	}

	while (reader_var != NULL)
	{
		if (strcmp(strtok(buffer, "\n"), reader_var->name) == 0)
		{
			printf("\"%s\"\n", reader_var->data);
			guardian = 1;
			break;
		}
		reader_var = reader_var->next;
	}

	if (guardian == 0)
	{
		printf("No variable \"%s\" in system memory.\n", buffer);
	}
}
