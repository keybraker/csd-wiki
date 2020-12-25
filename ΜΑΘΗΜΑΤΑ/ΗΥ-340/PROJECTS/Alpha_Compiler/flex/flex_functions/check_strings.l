int validEscapeChar(char c);

void string_check(alpha_token_t token ,char* token_content, enum token_enum token_type){

	int size = strlen(token_content);
	char buffer[size] ;
	int j = 0;
	int i = 0;
	
	string_starting_line = line_number_glb; // used for identifying the first line of string .

	for(i=1; i<strlen(token_content)-1; i++){

		if(token_content[i] == '\n')
			line_number_glb++;

		if(token_content[i] == '\\'){
			char c = validEscapeChar(token_content[i+1]);
			if( c != -1 ){ 
				if((i+1) < (strlen(token_content)-1)){ // this condition is to check the case "dawd\" which is wrong
					buffer[j] = c;
					j++;
					i++;
				}else{
					printf(ANSI_COLOR_RED	"\nError in string starting at line : %d" ANSI_COLOR_RESET "\n",line_number_glb);
					exit(0);
				}
			}else{
				printf(ANSI_COLOR_YELLOW	"\nUnknown escape character in string starting at line : %d" ANSI_COLOR_RESET "\n",line_number_glb);
				exit(0);	
			}
		}else{
			buffer[j] = token_content[i];
			j++;
		}
		
	}
	
	buffer[j] = 0;
	//create_instance(token,buffer,token_type);
}

int validEscapeChar(char c){ //return the ascii decimal number
	switch(c){
		case 'a' : return 7;
		case 'b' : return 8;
		case 'f' : return 12;
		case 'n' : return 10;
		case 'r' : return 13;
		case 't' : return 9;
		case 'v' : return 11;
		case '\\' : return 92;
		case '\'' : return 39;
		case '\"' : return 34;
		case '?' : return 63;
		default : return -1;
	}
}