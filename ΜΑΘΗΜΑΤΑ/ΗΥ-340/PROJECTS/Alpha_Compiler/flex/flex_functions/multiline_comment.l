alpha_token_t HEAD_comment ;
alpha_token_t END_comment ;

void create_instance_comments(alpha_token_t token, char* token_content, enum token_enum token_type);

void multiline_comments_check(alpha_token_t token, char* token_content, enum token_enum token_type){
	
	int current = input();
	int next = input();
	int opened_comments = 1;

	HEAD_comment = NULL;
	END_comment = NULL;

	create_instance_comments(token,token_content,token_type);

	while((current != EOF && next != EOF) && (current != 0 && next != 0)){

		if(current == '\n'){
			line_number_glb++;
		}
		
		if(next == '\n'){
			line_number_glb++;
		}
		/* An 2 diadoxikoi xaraktires den einai asterakia , tote elegxoume ton 2o gia to an einai /
		. An einai tote meta mporei na exoume asteraki ara na anoigei comment , epomenws o current ginetai
		next kai o next o epomenos apo ekei poy htan. An o 2os den einai / tote apla metatopizontai kata 2 .
		Diladi o current tha deixnei ston epomeno tou next kai o next ston epomeno tou neou current */

		if(current != '*' && next != '*'){
			if(next == '/'){		// case : /* a/ */ 
				current = next;
				next = input();
			}else{					//case : /* ab */
				current = input();
				next = input();
			}
		}else if(current != '*' && next == '*'){ /* Se auto to case mporoume na doume an anoigei kapoio sxolio an to 1o einai / . */
			if(current == '/'){		//case : /* /* */
				char nested_comment[] = "/* nested";
				create_instance_comments(token,nested_comment,token_type);
				opened_comments++;
				current = input();
				next = input();
			}else{				// case: /* a**/ . 
				current = next;
				next = input();
			}
		}else if(current == '*' && next != '*'){	/* Auti h case thekarei an kleinei kapoio comment kai an teleiwsame ton elegxo simfwna me ta opened comments .*/
			if(next == '/'){ 			// Vrikame ena kleisimo , ara meiwnoyme ta anoixta sxolia kata 1.
				opened_comments--;
				if(opened_comments == 0){
					break;
				}else{
					current = input();
					next = input();
				}
			}else {					// case : /* *a */
				current = input();
				next = input();
			}
		}else if(current == '*' && next == '*'){ /* Auti h periptwsi pianei ta 2 diadoxika asterakia */
			current = next;
			next = input();
		}

		

	} //end of while 


	if(opened_comments != 0){
		printf(ANSI_COLOR_RED"\nNon closing comment in line : %d" ANSI_COLOR_RESET "\n"  ,HEAD_comment->line);	
	}
		
	
}


void create_instance_comments(alpha_token_t token, char* token_content, enum token_enum token_type){

	
	token_number_glb++;

	token = (alpha_token_t)malloc(sizeof(struct alpha_token));
	token->token_content = (char*)malloc(1024);

	token->line = line_number_glb;
	token->token_number = token_number_glb;
	strcpy(token->token_content,token_content);
	token->token_type = token_type;

	if(HEAD_comment == NULL){
		token->next = END_comment;
		HEAD_comment = token;
		END_comment = token;
	}else{
		token->next = END_comment->next;
		END_comment->next = token;
		END_comment = token;
	}



	//printf("%d:  #%d \t \"%s\"   %s\n",token->line,token->token_number,token->token_content,getEnumString(token->token_type));

}
