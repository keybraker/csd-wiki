#include "cs345sh_header.h"

void man_func(void)
{
	printf("\nShell functions                October 18,2016                           Shell functions \n");
	printf("\033[33;1m \nNAME \033[0m\n");
	printf("\033[33;1m     cd, set, unset, printlvars, $var/exec, exit, pipe, redirection \033[0m -- all shell functions\n");
	printf("\033[33;1m \nLIBRARY \033[0m\n");
	printf("     Running program\n");
	printf("\033[33;1m \nSYNOPSIS \033[0m\n");
	printf("     void cd_func(char *sep_buffer)\n");
	printf("     void set_func(struct var *root_var, struct var *current_var)\n");
	printf("     void unset_func(struct var *root_var)\n");
	printf("     void printlvars_func(struct var *root_var)\n");
	printf("     void exec_func(char *buffer, struct var *root_var)\n");
	printf("     void executioner_direct(char *command)\n");
	printf("     void executioner_var(char *command)\n");
	printf("     void pipe_func(char *buffer, struct var *root_var)\n");
	printf("     void echo_func(char *buffer, struct var *root_var)\n");
	printf("     void man_func(void)\n");
	printf("     \n");
	printf("     \n");
	printf("\033[33;1m \nDESCRIPTION \033[0m\n");
	printf("     The cd_func takes you to the specified path\n");
	printf("     set functions saves a specified variable to system memory with its data\n");
	printf("     unset deletes data from a set variable\n");
	printf("     printlvars prints all variables in stored in memory\n");
	printf("     exec_func executes commands given by $ with command or variable\n");
	printf("     executioner_direct and executioner_var execute commands for different input\n");
	printf("     pipe_func pipes the putput of proccess one two proccess two\n");
	printf("     echo prints command on screen\n");
	printf("     man opens up manual ( to close press q)\n");
	printf("     \n");

	printf("\033[33;1m \nRETURN VALUES \033[0m\n");
	printf("     all functions are void so there are no return values\n");
	printf("\033[33;1m \nSTANDARDS \033[0m\n");
	printf("     All functions conforms to ISO/IEC 9899:1990 (``ISO C90'').\n");
	printf("\033[33;1m \nAUTHORS \033[0m\n");
	printf("     Ioannis Tsiakkas, UoC <csd3213@uoc.csd.gr>\n");
	printf("\nBSD                            October 18,2016                           BSD\n");

	size_t bufsize = 32;
	char *buffer = (char *)malloc(bufsize * sizeof(char));

	do
	{
		buffer = NULL;
		getline(&buffer, &bufsize, stdin);
		if (strcmp(strtok(buffer, "\n"), "q") == 0)
		{
			break;
		}
	} while (1);
	return;
}
