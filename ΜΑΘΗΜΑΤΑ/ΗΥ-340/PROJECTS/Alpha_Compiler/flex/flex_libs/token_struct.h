#include <stdio.h>
#include <stdlib.h>

enum token_enum
{
	KEYWORD,
	INTCONST,
	OPERATOR,
	DOUBLECONST,
	STRINGCONST,
	PUNCTUATION,
	IDENT,
	COMMENTS
};

typedef struct alpha_token
{
	int line;					// ari8mos grammis
	int token_number;			// ari8mos gia ka8e ena pou diabazei
	char *token_content;		// to periexomeno se string
	enum token_enum token_type; // ti einai auto to periexomeno
	struct alpha_token *next;	// o pointer gia tin lista

} *alpha_token_t;

int line_number_glb = 1;  // o ari8mos gia tin grammi
int token_number_glb = 0; // o ari8mos gia to periexomeno
int string_starting_line;

void multiline_comments_check(alpha_token_t token, char *token_content, enum token_enum token_type);
void string_check(alpha_token_t token, char *token_content, enum token_enum token_type);