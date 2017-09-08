#include "cs345sh_header.h"

void set_func(struct var *root_var, struct var *current_var)
{

	char *joker,*var_name=NULL, *var_data=NULL;;
	int guardian = 0;
	struct var *new_var; 

	var_name = strtok(NULL, " =\"\n");
	var_data = strtok(NULL, "=\"\n");

	joker = var_name;
	while(*joker)
	{
		if (!strchr(valid_characters, *joker))
			{ printf("%c, ", *joker); guardian = 1; }
   		joker++;
	}
	if(guardian == 1){
		printf("[ERROR: Use of unsupported character(s).]\n");
		printf("[NOTE: Please use a-z,A-Z,0-9,_ in variables names]\n");
		printf("-----------------–----------------------------\n");
		guardian = 0;
	}else{

		if(root_var->name == NULL && root_var->data == NULL && root_var->next == NULL){

			root_var->name = var_name;
			root_var->data = var_data;
			root_var->next = NULL;
					
			current_var = root_var;

		}else{
			// na tsekaro an mpainoun duo idia		
			new_var = (struct var *) malloc( sizeof(struct var) );

			new_var->name = var_name;
			new_var->data = var_data;
			new_var->next = NULL;

			current_var->next = new_var;
			current_var = current_var->next;

		}
	}
}

