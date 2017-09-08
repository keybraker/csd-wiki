#include "cs345sh_header.h"

int main() {

	char *name = NULL, *path = NULL, *buf = NULL, *buffer = NULL, *buffer_joker = NULL, *sep_buffer = NULL;

    size_t bufsize = 32;
    size_t buffer_size;

    struct var *root_var=NULL, *current_var=NULL;    

    root_var = (struct var *) malloc( sizeof(struct var) );
    root_var->name = NULL;
    root_var->data = NULL;
    root_var->next = NULL;
    current_var = root_var;

    printf(PrintBegin); 		
		
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL){ exit(1); }
    
    prev_path = getcwd(buf, (size_t)size);
		
	do{

		// current shell, current path, current user
		name = NULL;path = NULL;buffer = NULL;
		sep_buffer=NULL;buffer_joker=NULL;
		is_daemon = 0;daemon_pid=0;

		name = getlogin();
		if(name == NULL)
			{printf("error with User [NOT LOGGED IN]\n");}
		
		size = pathconf(".", _PC_PATH_MAX);
		if ((buf = (char *)malloc((size_t)size)) != NULL)
			{	path = getcwd(buf, (size_t)size); }
			
		if(path == NULL)
			{printf("error with path [NO DIRECTORY]\n\n");}

		// current shell, current path, current user
		if((name != NULL)||(path != NULL))
		{printf("%s@cs345sh%s/$ ",name,path);}

		// reading user input
		buffer_size = getline(&buffer,&bufsize,stdin); 	   	
		
		//printf("%zu characters were read.\n",buffer_size-1);
    	//printf("You typed: %s\n",buffer);

		//here is the check for symbol "|" "<", ">", ">>" 
    	char *joker = (char *)malloc(sizeof(char));
    	strcpy(joker,buffer);
    
    	int i = 0,guardian = 0,guardian_two = 0;
		while( joker[i] != '\n' ) 
	   	{
	   		if(joker[i] == '|')
	   			{ guardian = 1; }

	   		else if(joker[i] == '>')
	   			{
	   				guardian_two = 1; 
	   				if(joker[i+1] == '>') { guardian_two = 2; i++;}
	   			}

	   		else if(joker[i] == '<')
	   			{ guardian_two = 3; }

			else if(joker[i] == '&')
	   			{ buffer[i] = '\n';is_daemon = 1; }
			i++;
		}
	   	/////////////////////////////////
    	//separating string into words
    	sep_buffer = strtok(buffer, " ");

    	if(buffer[0] == '$')
			{
				//printf("EXECUTION HAS BEGAN buffer = %s\n",buffer);
				buffer_joker = buffer; 
			 	buffer_joker++;
				exec_func(buffer_joker, root_var);	
			}
    	else if(strcmp(sep_buffer,"cd") == 0)
			{ cd_func(sep_buffer); }

		else if(strcmp(sep_buffer,"set") == 0)
			{ set_func(root_var, current_var); }

		else if(strcmp(sep_buffer,"unset") == 0)
			{ unset_func(root_var); }

		else if(strcmp(strtok(buffer, "\n"),"printlvars") == 0)
			{ printlvars_func(root_var); }

		else if(strcmp(strtok(buffer, "\n"),"echo") == 0)
			{ echo_func(buffer, root_var); }

		else if(strcmp(strtok(buffer, "\n"),"man") == 0)
			{ man_func(); }

		else if(guardian == 1)
			{ pipe_func(buffer, root_var); }

		else if(guardian_two == 1)  
			{ redirection_func_type_one(buffer, root_var); }

		else if(guardian_two == 2)  
			{ redirection_func_type_two(buffer, root_var); }

		else if(guardian_two == 3)  
			{ redirection_func_type_three(buffer, root_var); }

		else if(strcmp(buffer,"\0") == 0)
			{ printf("'%s' : command not found\n",buffer); }
		else
			{ printf("'%s' : command not found\n",buffer); }
		
		if(is_daemon == 1){
	
			printf("%s with pid: %d is running in the backround.\n",buffer, daemon_pid);
						
			//unmask the file mode
			//umask(0);
			//set new session
			int sid = setsid();
			if(sid < 0)
			{exit(1);}
		}

	}while(strcmp(strtok(buffer, "\n"),"exit") != 0);
	
	printf(PrintEnding); 
    return 0;
}

