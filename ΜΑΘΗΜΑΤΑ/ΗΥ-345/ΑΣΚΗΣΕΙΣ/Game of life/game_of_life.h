/**********************************************************************
 * @file   game_of_life.h                                           *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>  			          *
 *                                                                    *
 * @brief  Header file with the structures and function prototypes    *
 * for the needs of the Operating Systems (HY-345) ask2 (Fall 2016)	  *
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
#include <pthread.h>
#include <curses.h>

/*Variables*/
int lifeTable[100][100]; 	// every block can be of state 1-0, alive-dead
int lifeTable_fake[100][100]; 	// every block can be of state 1-0, alive-dead

/*Struct for arguments*/
struct arg_struct {
    int x;
    int y;
};

/*Needed function definition*/
extern int file_reader(char *filename);
extern void *exec_hundredth(void *arguments);
extern void print_life();
