#include "game_of_life.h"

int file_reader(char *filename)
{

	char ch;
	int i = 0, j = 0;

	FILE *ptr_file;
	ptr_file = fopen(filename, "r");

	if (!ptr_file)
	{
		fprintf(stderr, "file failed to open.\n");
		return 1;
	}

	while ((ch = getc(ptr_file)) != EOF)
	{
		if (j == 100)
		{
			i++;
			j = 0;
		}

		if (ch == '0')
		{
			lifeTable[i][j] = 0;
			lifeTable_fake[i][j] = 0;
			j++;
		}
		else if (ch == '1')
		{
			lifeTable[i][j] = 1;
			lifeTable_fake[i][j] = 1;
			j++;
		}
	}

	fclose(ptr_file);
	return 0;
}
