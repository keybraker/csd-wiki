#include "cs345sh_header.h"

void go_func(char *path)
{

	int answer = chdir((const char *)path);
	if (answer == 0)
	{
		// printf("directory changed\n");
	}
	else
	{
		switch (answer)
		{
		case EACCES:
			printf("Permission denied");
			break;
		case EIO:
			printf("An input output error occured");
			break;
		case ENAMETOOLONG:
			printf("Path is to long");
			break;
		case ENOTDIR:
			printf("A component of path not a directory");
			break;
		case ENOENT:
			printf("No such file or directory");
			printf("enoent\n");
		default:
			printf("Couldn't change directory to %s\n", path);
		}
	}
}

void cd_func(char *sep_buffer)
{

	char *joker_path, *buf = NULL;
	sep_buffer = strtok(NULL, " \n");

	if (strcmp(sep_buffer, "-") == 0)
	{
		joker_path = prev_path;
		prev_path = getcwd(buf, (size_t)size);
		go_func(joker_path);
	}
	else if (strcmp(sep_buffer, "~") == 0)
	{
		prev_path = getcwd(buf, (size_t)size);
		go_func("/home"); // home directory changes every time
	}
	else
	{
		prev_path = getcwd(buf, (size_t)size);
		go_func(strtok(sep_buffer, " \n"));
	}
	return;
}
