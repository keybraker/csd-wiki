#include "cs345sh_header.h"

void execv_args_creator(char *command, char *args[])
{

	int i = 0;

	args[0] = (char *)malloc(sizeof(char));
	strcpy(args[0], strtok(command, " "));

	char *joker = strtok(NULL, " \0\n");

	i = 1;
	while (joker != NULL)
	{

		args[i] = (char *)malloc(sizeof(char));
		strcpy(args[i], joker);

		joker = strtok(NULL, " \0\n");
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

void pipe_func(char *buffer, struct var *root_var)
{

	int i = 0, one_i = 0, two_i = 0, guardian = 0, k = 0;

	char *args_one[200] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
						   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	char *args_two[200] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
						   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	char *exec_one = (char *)malloc(sizeof(char));
	char *exec_two = (char *)malloc(sizeof(char));

	i = 0;
	while (buffer[i] != '\n')
	{
		if (buffer[i] == '|')
		{
			guardian = 1;
			i++;
		}

		if (guardian == 0)
		{
			exec_one[one_i] = buffer[i];
			one_i++;
		}
		else if (guardian == 1)
		{
			exec_two[two_i] = buffer[i];
			two_i++;
		}

		i++;
	}
	exec_one[one_i + 1] = '\n';
	exec_two[two_i + 1] = '\n';

	k = 0;
	while (exec_one[k] == ' ')
	{
		k++;
	}
	while (k > 0)
	{
		exec_one++;
		k--;
	}

	k = 0;
	while (exec_two[k] == ' ')
	{
		k++;
	}
	while (k > 0)
	{
		exec_two++;
		k--;
	}

	i = 0;
	while (exec_one[i] != '\n')
	{
		if (exec_one[i] == '\0')
		{
			exec_one[i] = ' ';
		}
		i++;
	}
	i = 0;
	while (exec_two[i] != '\n')
	{
		if (exec_two[i] == '\0')
		{
			exec_two[i] = ' ';
		}
		i++;
	}

	exec_one = strtok(exec_one, "\n");
	exec_two = strtok(exec_two, "\n");

	execv_args_creator(exec_one, args_one);
	execv_args_creator(exec_two, args_two);

	////////////////////////////////////// CREATED TWO PATHS FOR EXECV //////////////////////////////////////

	// creating pipe
	int check, pipefd[2];
	check = pipe(pipefd);
	if (check == -1)
	{
		perror("pipe failed");
		exit(1);
	}

	// first child
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(1);
	}
	else if (pid == 0)
	{
		// printf("pipe: I am the first child with pid = %d\n", (int) getpid());

		dup2(pipefd[0], 0);
		close(pipefd[1]);

		execvp(args_two[0], args_two);
		fprintf(stderr, "Exec failed\n");
	}

	// second child
	pid_t pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork failed.");
		exit(1);
	}
	else if (pid2 == 0)
	{
		// printf("pipe: I am the second child with pid = %d\n", (int) getpid());

		dup2(pipefd[1], 1);
		close(pipefd[0]);

		execvp(args_one[0], args_one);
		fprintf(stderr, "Exec failed\n");
	}

	// printf("pipe: I am the parent with pid = %d, waiting for the child to end\n", (int) getpid());
	wait(NULL);
}

// ps axl | grep zombie
