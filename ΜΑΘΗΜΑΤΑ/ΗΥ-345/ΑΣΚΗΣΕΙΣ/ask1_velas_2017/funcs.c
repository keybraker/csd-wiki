#include "funcs.h"

void ctrl_sq() {
	static struct termios config;

	if(!isatty(STDIN_FILENO)) {  perror("fd"); }
	// Get the current configuration of the serial interface
	if(tcgetattr(STDIN_FILENO, &config) < 0) { perror("tcGetattr"); }
	config.c_iflag = IXON;
	//Wait until all output written to file descriptor fd has been transmitted.
	//tcdrain(STDIN_FILENO);
 	// Finally, apply the configuration
	if(tcsetattr(STDIN_FILENO,  TCSAFLUSH, &config) < 0) {  perror("tcSetattr");}
}

void
print_prompt()
{
	
	long size = pathconf(".", _PC_PATH_MAX);
	
	char* pathbuf = (char *) malloc((size_t)size);

	printf("%s@cs345sh%s ",getlogin(),getcwd(pathbuf,size));
}

char*
parse(void)
{
	char *buffer;
    size_t bufsize = 64; /* XD the getline slave allocate a buffer */

    buffer = (char*) malloc(bufsize * sizeof(char));

    if (buffer == NULL) {
    	perror("Unable to allocate buffer");
        exit(1);
    }

    getline(&buffer, &bufsize, stdin);

    return buffer;
}

char**
tokenize(char* s)
{
	int bufsize = SIZE, index = 0;
	char** tokens = malloc(bufsize  * sizeof(char*));
	char* token;

	if(!tokens) {
		fprintf(stderr, "TOKENS: allocation error\n");
    	exit(EXIT_FAILURE);
	}

	token = strtok(s, DELIM);
	while(token != NULL) {
		tokens[index] = token;
		index++;

		if(index >= bufsize) {
			bufsize += SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			
			if(!tokens){
				perror("realloc error!");
        		exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIM);
	}

	tokens[index] = NULL;

	return tokens;
}