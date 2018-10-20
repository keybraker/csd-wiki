#include "cs345sh_header.h"

//////////////////////////////////////////////////////////////////////////////////////////////// ls -l my_files/ >> output_file

void redirection_func_type_one(char *buffer, struct var *root_var){ 

	int i = 0, k = 0 ;

	char* args_one[200] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
					   	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL  };

	char *exec_one = (char *)malloc(sizeof(char));
	char *file_to_redirect_stdout = (char *)malloc(sizeof(char));

	i=0;
	while( buffer[i] != '\n') 
	{
		if(buffer[i] == '\0'){buffer[i]=' ';}
		if(buffer[i] == '\t'){buffer[i]=' ';}

		i++;
	}

	char *joker = (char *)malloc(sizeof(char));
	joker = strtok(buffer, " \n\0\t");
	i=0;k=0;
	while(joker != NULL){
		
		if(strcmp(joker,">") == 0){k=1;i=0;joker = strtok(NULL, " \n\0\t");}

		if (k == 0)
		{
			if (i == 0)
			{ strcpy(exec_one,joker); i++;}
			else
			{ strcat(exec_one, " ");strcat(exec_one,joker); }
		}
		else
		{
			if (i == 0)
			{ strcpy(file_to_redirect_stdout,joker); i++;}
			else
			{ strcat(file_to_redirect_stdout,joker); }
		}
		
		joker = strtok(NULL, " \n\0\t");
	}

	execv_args_creator(exec_one,args_one);

	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(1);
	}
	else if (pid == 0){ //printf("pipe: I am the first child with pid = %d\n", (int) getpid());	
		
		// anoigo to arxeio kai kano redirect to info tou sto stdin
		FILE *ptr_file;
		ptr_file = fopen(file_to_redirect_stdout, "w");

		if (!ptr_file){
			fprintf(stderr, "file failed to open\n");
		}

		dup2(fileno(ptr_file),fileno(stdout));
		// kleino to arxeio
		fclose(ptr_file);

		execvp(args_one[0], args_one);
	   	fprintf(stderr, "Exec failed\n");
		
	}
	else{ wait(NULL); }

}



