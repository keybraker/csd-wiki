%{
	#include <stdio.h>
	#include <string.h>
	
	#include "parser.h"
	#include "../Alpha_Compiler/flex/flex_libs/token_struct.h"
	
	#define ANSI_COLOR_RED		"\x1b[41m"
	#define ANSI_COLOR_RESET   "\x1b[0m"
	#define ANSI_COLOR_YELLOW  "\x1b[33m"
	
	void create_instance(alpha_token_t token , char* token_content, enum token_enum token_type);
	char* getEnumString(int enumID);
%}

%option noyywrap
%option yylineno

%%
"if"		{return IF;}//create_instance(yyval,"if",KEYWORD);
"else"		{return ELSE;}//create_instance(yyval,"else",KEYWORD);	
"while"		{return WHILE;}//create_instance(yyval,"while",KEYWORD);
"for"		{return FOR;}//create_instance(yyval,"for",KEYWORD);
"function"	{return FUNCTION;}//create_instance(yyval,"function",KEYWORD);
"return"	{return RETURN;}//create_instance(yyval,"return",KEYWORD);
"break"		{return BREAK;}//create_instance(yyval,"break",KEYWORD);
"continue"	{return CONTINUE;}//create_instance(yyval,"continue",KEYWORD);
"and"		{return AND;}//create_instance(yyval,"and",KEYWORD);
"not"		{return NOT;}//create_instance(yyval,"not",KEYWORD);
"or"		{return OR;}//create_instance(yyval,"or",KEYWORD);
"local"		{return local;}//create_instance(yyval,"local",KEYWORD);
"true"		{return TRUE;}//create_instance(yyval,"true",KEYWORD);
"false"		{return FALSE;}//create_instance(yyval,"false",KEYWORD);
"nil"		{return NIL;}//create_instance(yyval,"nil",KEYWORD);
"="			{return equal;}//create_instance(yyval,"=",OPERATOR);
"+"			{return plus;}//create_instance(yyval,"+",OPERATOR);
"-"			{return minus;}//create_instance(yyval,"-",OPERATOR);
"*"			{return mul;}//create_instance(yyval,"*",OPERATOR);
"/"			{return divide;}//reate_instance(yyval,"/",OPERATOR);
"%"			{return percent;}//create_instance(yyval,"%",OPERATOR);
"=="		{return equalequal;}//create_instance(yyval,"==",OPERATOR);
"!="		{return notequal;}//create_instance(yyval,"!=",OPERATOR);
"++"		{return plusplus;}//create_instance(yyval,"++",OPERATOR);
"--"		{return minusminus;}//create_instance(yyval,"--",OPERATOR);
">"			{return greater;}//create_instance(yyval,">",OPERATOR);
"<"			{return lesser;}//create_instance(yyval,"<",OPERATOR);
">="		{return greaterequal;}//create_instance(yyval,">=",OPERATOR);
"<="		{return lesserequal;}//create_instance(yyval,"<=",OPERATOR);
"{"			{return openblock;}//create_instance(yyval,"{",PUNCTUATION);
"}"			{return closeblock;}//create_instance(yyval,"}",PUNCTUATION);
"["			{return openbracket;}//create_instance(yyval,"[",PUNCTUATION);
"]"			{return closebracket;}//create_instance(yyval,"]",PUNCTUATION);
"("			{return openpar;}//create_instance(yyval,"(",PUNCTUATION);
")"			{return closepar;}//create_instance(yyval,")",PUNCTUATION);
";"			{return semicolon;}//create_instance(yyval,";",PUNCTUATION);
","			{return comma;}//create_instance(yyval,",",PUNCTUATION);
":"			{return colon;}//create_instance(yyval,":",PUNCTUATION);
"::"		{return coloncolon;}//create_instance(yyval,"::",PUNCTUATION);
"."			{return dot;}//create_instance(yyval,".",PUNCTUATION);
".."		{return dotdot;}//create_instance(yyval,"..",PUNCTUATION);
"/*"		{ 
				alpha_token_t yyval;
				multiline_comments_check(yyval,"/*",COMMENTS);
			}
"//"		{ 
				int c;
				while((c = input()) != '\n' && c != EOF && c != 0) ; // ignore all chars till you find a new line char.
					line_number_glb++;
			}
"\n"		{line_number_glb++;}

[0-9]+\.[0-9]* {double d ; sscanf(yytext,"%lf",&d); yylval.numVal = d; return NUMBER;}//create_instance(yyval,yytext,DOUBLECONST);
[0-9]+ {double d ; sscanf(yytext,"%lf",&d); yylval.numVal = d; return NUMBER;}//create_instance(yyval,yytext,INTCONST);
[a-zA-Z][a-zA-Z0-9_]* {yylval.strVal = strdup(yytext); return ID;}//create_instance(yyval,yytext,IDENT);
[\"]([^"]|\\.)*[\"] { //"dexetai autaki kai meta eite \(ecape char) eite opoiodipote char ektos apo " , kai kleinei se "
						alpha_token_t yyval;
						string_check(yyval,yytext,STRINGCONST);
						yylval.strVal = strdup(yytext);
						return STRING;
					}
[\"][^"]* {printf(ANSI_COLOR_RED	"\nNon closing string at line : %d" ANSI_COLOR_RESET "\n" ,line_number_glb );}
[ \t]* /* ignores whitespaces */;

.	{printf(ANSI_COLOR_RED	"\nUnexistent Type ' %s ' In Line : %d !"	ANSI_COLOR_RESET"\n"  ,yytext,line_number_glb);}

%%


/*
* input  : 	oles tis aparaithtes plirofories gia na dimiourghsei neo 
*			struct tupou alpha_token
*
* 		   	Dimiourgei ena neo alpha_token me malloc
* 			kai to fortonei me tis dosmenes plirofories
*
* return : 	to neo alpha_token
*/

int getCurrentLine(){
	return line_number_glb;
}

void create_instance(alpha_token_t head ,char* token_content, enum token_enum token_type){

	token_number_glb++;
	alpha_token_t token = (alpha_token_t)malloc(sizeof(struct alpha_token));
	alpha_token_t reader = head;
	
	if(token_type == STRINGCONST){
		token->line = string_starting_line; // declared in token.h and modified in check_strings.l
	}else{
		token->line = line_number_glb;
	} 
	token->token_number = token_number_glb;
	token->token_content = strdup(token_content);
	token->token_type = token_type;
	token->next = NULL;

	if(head->line == 0){
		head->line = token->line;
		head->token_number =  token->token_number ;
		head->token_content = token->token_content ;
		head->token_type = token->token_type ;
	}else{
		while(reader->next != NULL){
			reader = reader->next;
		}
		reader->next = token;
	}
	printf("create\n");
	//printf("%d:  #%d \t \"%s\"   %s\n",token->line,token->token_number,token->token_content,getEnumString(token->token_type));

}




/*
*			ena aplo enum -> word converter
*
*/
char* getEnumString(int enumID){
	switch(enumID){
		case 0 : return "KEYWORD";
		case 1 : return "INTCONST";
		case 2 : return "OPERATOR";
		case 3 : return "DOUBLECONST";
		case 4 : return "STRINGCONST";
		case 5 : return "PUNCTUATION";
		case 6 : return "IDENT";
		case 7 : return "COMMENTS";
		default : return "UKNOWN";
	}
}
