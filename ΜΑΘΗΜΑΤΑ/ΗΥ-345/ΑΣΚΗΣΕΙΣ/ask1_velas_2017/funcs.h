#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 64
#define DELIM " \t\r\n\a"

void print_prompt();
char* parse(void);
char** tokenize(char* s);
void ctrl_sq();

#endif