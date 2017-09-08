/**********************************************************************
 * @file   cs345sh_header.h                                           *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>  			          *
 *                                                                    *
 * @brief  Header file with the structures and function prototypes    *
 * for the needs of the Operating Systems (HY-345) ask1 (Fall 2016)	  *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define valid_characters "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_\n"
#define PrintBegin "⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞⏞\ncs345sh execution has begun.\n----------------------------\n"
#define PrintEnding "----------------------------\ncs345sh execution has ended.\n⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟⏟\n"

/*Needed structs definition*/
struct var {
  char *name, *data;
  struct var *next;
};

char *prev_path;
long size;
int is_daemon;
int daemon_pid;

/*Needed function definition*/
extern void cd_func(char *sep_buffer);
extern void set_func(struct var *root_var, struct var *current_var);
extern void unset_func(struct var *root_var);
extern void printlvars_func(struct var *root_var);
extern void exec_func(char *buffer, struct var *root_var);
extern void executioner_direct(char *command);
extern void executioner_var(char *command);
extern void pipe_func(char *buffer, struct var *root_var);

extern void execv_args_creator(char *command,char *args[]);

extern void redirection_func_type_one(char *buffer, struct var *root_var);
extern void redirection_func_type_two(char *buffer, struct var *root_var);
extern void redirection_func_type_three(char *buffer, struct var *root_var);

extern void echo_func(char *buffer, struct var *root_var);
extern void man_func(void);

/*
extern	char *joker;
extern	char *name; 
extern  char *path; 
extern  char *buf; 
extern  char *buffer; 
extern  char *buffer_cpy; 
extern  char *sep_buffer; 
extern  char *var_name;
extern  char *var_data;
extern	int answer;
extern	int guardian;
extern	long size;
extern  size_t bufsize;
extern  size_t buffer_size;


extern struct var *root_var;
extern struct var *current_var; 
extern struct var *new_var;
extern struct var *reader_var;  
*/


