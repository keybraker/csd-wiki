/**
 * Assignment 1 hy345 c shell
 *
 * @author csd3319
 * @version 0.1 02/03/2018
 */

#include "funcs.h"

int main() {

	pid_t bg[10];
	pid_t pid;
	pid_t tpid;
	int status;
	char** array;
	char* command;
	char* arg1;
	char* arg2;
	char* out;
	char* in;
	char* ena;
	char* dyo;
	char* tria;
	char* tessera;
	char* pente;
	int flag1 = 0;
	int metritis = 0;
	int back = 0;
	
	//ctrl_sq();

	while(1) {
	
	print_prompt();
	command = parse();

	char* temp = strdup(command);
	char* temp_command = strdup(command);	

	arg2 = strchr(temp, '|');
	out = strchr(temp, '>');
	in = strchr(temp, '<');



	while(temp_command) {
		char* temp2 = strdup(temp_command);
		char* dimitris;

		dimitris = strtok( temp2, " ");
		
		if (strcmp(dimitris, "exit\n") == 0)
		{
			return 1;
		}else if (strcmp(dimitris, "cd") == 0) {
			char* dir = strtok(NULL, "\n");
			strcat(dir,"/");
			
			
			int ret;
			ret = chdir(dir);
			break;

		}else if (strcmp(dimitris, "fg\n") == 0) {
			//printf("NAI MPIKA TEEE\n");
			//tcsetpgrp(0,bg[0]);
			kill(bg[0], SIGCONT);
			temp_command = '\0';
		}else{

		}


		 dyo = strchr(temp_command, '>');
		

		if (ena = strchr(temp_command, '|')){
			//printf("*** has pipe ***\n");

			int pipefd[2];
			pid_t pid;
			int count = 0;
			char bin[100];
			char** array;
			char* lvalue = strsep(&temp_command, "|");

			
			array = tokenize(lvalue);
			strcpy(bin, array[0]); /* first command that the child must execute */

			//printf("bin is  -%s- \n", bin);
			/* kalitera na balw strdup */
			array[0] = bin;

			while (array[count] != NULL) {
				count++;
			}

			array[count] = (char*) NULL;

			if (pipe(pipefd)==-1){
				fprintf(stderr, "Pipe Failed" );
				return 1;
			}

			pid = fork();

			if (pid == -1){
				perror("fork");
				exit(EXIT_FAILURE);
			}else if (pid == 0) {
				/* child */
       		    /* do redirections and close the wrong side of the pipe */
				close(pipefd[0]); /* the other side of the pipe */
				dup2(pipefd[1],1);  /* automatically closes previous fd 1 */
				close(pipefd[1]);  /* cleanup */

				execvp(bin,array);
				
				/* return value from execl() can be ignored because if execl returns
         		* at all, the return value must have been -1, meaning error; and the
         		* reason for the error is stashed in errno */
		       	perror("error on child execv in pipe state");
		       	exit(1);

			}else {
				/* parent */
        /*
         * It is important that the last command in the pipeline is execd
         * by the parent, because that is the process we want the shell to
         * wait on.  That is, the shell should not loop and print the next
         * prompt, etc, until the LAST process in the pipeline terminates.
         * Normally this will mean that the other ones have terminated as
         * well, because otherwise their sides of the pipes won't be closed
         * so the later-on processes will be waiting for more input still.
         */
        /* do redirections and close the wrong side of the pipe */
				pid = fork();
				if(pid == 0) {				
				close(pipefd[1]); /* the other side of the pipe */
                dup2(pipefd[0], 0);  /* automatically closes previous fd 0 */
                close(pipefd[0]); /* cleanup */
				char* temp;
				char* check = strchr(ena+2, '>');
				if (check != NULL )
				{	
					/***************************************************************************************** */
					ena = ena + 2;
					temp = strdup(strsep(&ena, ">"));

					char** array = tokenize(temp);
					char bin[100];
					strcpy(bin,array[0]); 
					
					array[0] = strdup(bin);

					int count = 0;
					while (array[count] != NULL) {
						count++;
					}

					array[count] = NULL;

					strsep(&ena, " ");
					char* rvalue = strdup(strsep(&ena, "\n"));
					/*printf("ENA rvalue (%s)\n", rvalue);*/

					int file = open(rvalue,  O_CREAT | O_WRONLY);
					if(file < 0)    return 1;

					/*Now we redirect standard output to the file using dup2 */
					if(dup2(file,1) < 0)    return 1;


	                execvp(bin,array);
	                /*fclose(fp); */
	                close(file);
	                exit(1);
					}else{ 
						/* paizei kata 99.9999% na min xreiazete xd :P*/
					} 

					/*aplo pipe implementation*/
					char** array = tokenize(ena+2);
					char bin[100];
					strcpy(bin,array[0]); 
					
					array[0] = strdup(bin);

					int count = 0;
					while (array[count] != NULL) {
						/*printf("array = -%s-\n", array[count]);*/
						count++;
					}

					array[count] = NULL;

	                execvp(bin,array);
	                exit(1);

	            	}else{
	            		close(pipefd[0]);
	            		close(pipefd[1]);
					 	waitpid(pid, &status, 0);
					 	temp_command = '\0';
	            	}
			
            }

		}else if(tria = strchr(temp_command, '<')){
			//printf("*** has < ***\n");

			if ((pid = fork()) == -1){

				exit(EXIT_FAILURE);
				perror("fork error");
			}else if (pid == 0) {

				int in, out;
				int count = 0;
				char param1[100];

				char** array;
				char* lvalue;
				char* rvalue;

				char temp[100];
				char tempp[100];
				const char s[3] = ">";
				const char ss[3] = " ";

				char* a = strdup(temp_command);
				char b[100];
				lvalue = strdup(strsep(&temp_command, "<"));

				strcpy(temp,strtok(a+1, s));
				strcpy(temp,strtok(a,"\n"));

				strcpy(temp, strtok(temp+6, "\n"));
				strcpy(temp, strtok(temp, " "));

				if (strchr(temp_command, '>'))
				{	
					strsep(&temp_command, ">");
					flag1 = 1;
					
					temp_command += 1;
					temp_command = strsep(&temp_command, "\n");
					
				}else{
					flag1 = 0;
					temp_command += 1;
					rvalue = strdup(strsep(&temp_command, "\n"));
				}

				array = tokenize(lvalue);

				//strcpy(param1,"/bin/");
				strcpy(param1,array[0]);
				
				array[0] = param1;
				/*array = realloc(array, sizeof(char*)); */

				while (array[count] != NULL) {
					count++;
				}

				array[count] = NULL;
				
				/* open input and output files */
				in = open(temp,  O_RDONLY);
				if(in < 0)    perror("ERROR open input file");

				/* replace standard input with input file */
				dup2(in, STDIN_FILENO);
				
				if (flag1 == 1){
					out = open(temp_command, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				  	if(out < 0)    perror("ERROR open output file");

				  	/*replace standard output with output file */
					dup2(out, STDOUT_FILENO);
					
				}

				/*
				FILE *fp;  
				fp = freopen(rvalue, "r", stdin);
				
				execlp(param1, array[0], (char*)NULL
				*/
	

			    execvp(param1, array);
			    close(in);
				close(out);
			    
			   /* fclose(fp); */

			}else{
				/* This is run by the parent.  Wait for the child
		        to terminate. */
		        
			 	waitpid(pid, &status, 0);
			 	temp_command = '\0';
			}
			

		}else if(dyo && dyo[1] != '>'){
			
			//printf("*** has > ***\n");

			if ((pid = fork()) == -1){

				exit(EXIT_FAILURE);
				perror("fork error");
			}else if (pid == 0) {

				int count = 0;
				char param1[100];
				char** array;
				char* lvalue;
				char* rvalue;
				
				
				lvalue = strdup(strsep(&temp_command, ">"));
				temp_command += 1; /* skipare to space meta to > */
				rvalue = strdup(strsep(&temp_command, "\n"));

				array = tokenize(lvalue);

				//strcpy(param1,"/bin/");
				strcpy(param1,array[0]);
				
				array[0] = param1; 

				while (array[count] != NULL) {
					count++;
				}

				
				array[count] = NULL;
				count = 0;
				/*
				First, we're going to open a file 

				int file = open(rvalue,  O_CREAT | O_WRONLY);
				if(file < 0)    return 1;

				//Now we redirect standard output to the file using dup2
				if(dup2(file,1) < 0)    return 1;
				*/
				FILE *fp;
				fp = freopen(rvalue, "w+", stdout);

			    execvp(param1, array);
			    perror("Return not expected. Must be an execv error.n");


			    fclose(fp);


			}else{
				/* This is run by the parent.  Wait for the child
		        to terminate. */
		        temp_command = '\0';
			 	waitpid(pid, &status, 0);
			}


		}else if(tessera = strchr(temp_command, '>')) {
			//printf("*** has >> ***\n");

			if ((pid = fork()) == -1){

				exit(EXIT_FAILURE);
				perror("fork error");
			}else if (pid == 0) {

				int count = 0;
				char param1[100];
				char** array;
				char* lvalue;
				char* rvalue;
				
				lvalue = strdup(strsep(&temp_command, ">"));
				temp_command +=2; /* skip ">space" */
				rvalue = strdup(strsep(&temp_command, "\n"));
				

				
				array = tokenize(lvalue);

				strcpy(param1,"/bin/");
				strcat(param1,array[0]);
				
				array[0] = param1;
				/* array = realloc(array, sizeof(char*)); */

				while (array[count] != NULL) {
					count++;
				}

				array[count] = NULL;

				
				/*First, we're going to open a file */

				FILE *fp;
				fp = freopen(rvalue, "a+", stdout);
				
				/*
				int file = open(rvalue,  O_APPEND| O_CREAT | O_WRONLY);
				if(file < 0)    return 1;

				//Now we redirect standard output to the file using dup2
				if(dup2(file,1) < 0)    return 1;*/

			    execv(param1, array);
			    perror("Return not expected. Must be an execv error.n");

			    fclose(fp);

			}else{
				/* This is run by the parent.  Wait for the child
		        to terminate. */
		        temp_command = '\0';
			 	waitpid(pid, &status, 0);
			}



		}/*else if (pente = strchr(temp_command, '&')){
			printf("*** has & ***\n");


		}*/else {
			char buff[200];
			/*exw mia opoiadipote apli entoli me h xwris tis parametrous tis kai tin ektelw */
			if (strchr(temp_command, '&') != NULL )
			{
				back = 1;
				strcpy(buff, strtok(temp_command, "&"));
				printf("BUFF without & -%s-\n", buff);
			}else {

			}//if &

			char* param1 = strtok(buff, "\n");
			/*printf("param1 (%s)", param1);
			printf("temp_command (%s)", temp_command);*/	
			array = tokenize(temp_command);
			if ((pid = fork()) == -1){

				exit(EXIT_FAILURE);
				perror("fork error");
			}else if (pid == 0) {
				int count = 0;

				while (array[count] != NULL) {
					count++;
				}
				
				//printf("1PGID %d\n", getpgrp());
				setpgid(0,0); //puts the child in a new process group whose group ID is identical to the child’s PID
				//setsid();
				//printf("2PGID %d\n", getpgrp());
				if (back == 1)
				{
					execvp(array[0], array);
					perror("Return not expected. Must be an execvp error.n");
					//exit(0);
 
				}else{
					execvp(array[0], array);
					perror("Return not expected. Must be an execvp error.n");
				}
			}else{
				/* This is run by the parent.  Wait for the child
				to terminate. */
				if (back == 1)
				{
					//sleep(1);
					bg[0] = pid;
					/*The default action for SIGTSTP is to place a process in the stopped state,
					  where it remains until it is awakened by the receipt of a SIGCONT signal. */
					kill(pid, SIGTSTP); //  
					//signal(SIGCHLD, SIG_IGN); /* ignore child */
					back = 0;
					temp_command = '\0';
					//waitpid(pid, &status, WNOHANG);
				}else{
					temp_command = '\0';
					waitpid(pid, &status, 0);
				}
				}

		}
	
	}/*end of while(temp_command)*/



 }/*end of while*/	


	return 0;
}
