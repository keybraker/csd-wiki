#include "cs345sh_header.h"
// set rikas=ls -al
void executioner_direct(char *command)
{

	int i = 0, m = 0, n = 0;
	char *args[20] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	args[0] = (char *)malloc(sizeof(char));
	strcpy(args[0], "/bin/");
	strcat(args[0], command);

	char *joker = strtok(NULL, " \0");
	//= strtok(command, " ");

	// printf("joker = |%s|\n",joker);
	// printf("args[%d] = |%s|\n",i, args[i]);

	i = 0, m = 0, n = 1;
	if (joker == NULL)
	{
		// printf("mpika sto 1\n" );

		i = 0;
		while (command[i] != '\n')
		{
			// printf("command[%d] = %c\n",i, command[i]);

			if (command[i] == '\0')
			{
				m = i;
				i = -1;
				while (m >= 0)
				{
					command++;
					m--;
				}
				joker = strtok(command, " ");
				args[n] = (char *)malloc(sizeof(char));
				args[n] = joker;
				n++;

				// printf("	new_command = %s\n", joker);
			}
			if (command[i] == ' ')
			{
				m = i;
				i = -1;
				while (m >= 0)
				{
					command++;
					m--;
				}
				joker = strtok(command, " ");
				args[n] = (char *)malloc(sizeof(char));
				args[n] = joker;
				n++;

				// printf("	new_command = %s\n", joker);
			}
			i++;
		}
	}

	else
	{ // printf("mpika sto 2\n" );

		i = 1;
		while (joker != NULL)
		{
			args[i] = (char *)malloc(sizeof(char));

			args[i] = joker;

			// printf("joker = %s\n",joker);
			// printf("args[%d] = %s\n",i, args[i]);

			joker = strtok(NULL, " \n");
			i++;
		}
	}

	i = 0;
	while (args[i] != NULL)
	{
		args[i] = strtok(args[i], "\n");
		// printf("args[%d] = |%s|\n",i, args[i] );
		i++;
	}
	execv(args[0], args);
}

void executioner_var(char *command)
{

	char *joker = strtok(command, " ");
	char *args[20] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	int i = 0;

	while (joker != NULL)
	{
		args[i] = (char *)malloc(sizeof(char));
		if (i == 0)
		{
			strcpy(args[i], "/bin/");
			strcat(args[i], joker);
		}
		else
		{
			args[i] = joker;
		}

		joker = strtok(NULL, " \n");
		i++;
	}
	execv(args[0], args);
}

void exec_func(char *buffer, struct var *root_var)
{
	int guardian = 0;
	pid_t pid;

	if (buffer[0] == 0)
	{
		printf("ERROR: command must not be separated by symbol '$'\n");
		return;
	}

	// printf("INSIDE EXECUTION HAS BEGAN buffer = |%s|\n",buffer);

	if (root_var->name != NULL)
	{
		struct var *reader_var = root_var;
		while (reader_var != NULL)
		{
			if (strcmp(reader_var->name, strtok(buffer, "\n")) == 0)
			{
				guardian = 1;
				// if variable is matching a fork is created
				pid = fork();
				if (pid < 0)
				{
					perror("fork failed.");
					exit(1);
				}
				else if (pid == 0)
				{
					// printf("I am the child with pid = %d\n", (int) getpid());

					executioner_var(reader_var->data);

					if (is_daemon == 1)
					{
						printf("mpika2\n");
						daemon_pid = (int)getpid();
						// unmask the file mode
						umask(0);
						// set new session
						int sid = setsid();
						if (sid < 0)
						{
							// Return failure
							exit(1);
						}
						// Change the current working directory to root.
						chdir("/");
						// Close stdin. stdout and stderr
						close(STDIN_FILENO);
						close(STDOUT_FILENO);
						close(STDERR_FILENO);
					}
				}
				else
				{
					if (is_daemon == 1)
					{
						return;
					}
					wait(NULL);
				}
			}
			reader_var = reader_var->next;
		}
	}
	if (guardian == 0)
	{

		pid = fork();
		if (pid < 0)
		{
			perror("fork failed.");
			exit(1);
		}
		else if (pid == 0)
		{
			executioner_direct(buffer);

			if (is_daemon == 1)
			{
				printf("mpika2\n");
				daemon_pid = (int)getpid();
				// unmask the file mode
				umask(0);
				// set new session
				int sid = setsid();
				if (sid < 0)
				{
					// Return failure
					exit(1);
				}
				// Change the current working directory to root.
				chdir("/");
				// Close stdin. stdout and stderr
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				close(STDERR_FILENO);
			}
		}
		else
		{
			if (is_daemon == 1)
			{
				return;
			}
			wait(NULL);
		}
	}
	return;
}
