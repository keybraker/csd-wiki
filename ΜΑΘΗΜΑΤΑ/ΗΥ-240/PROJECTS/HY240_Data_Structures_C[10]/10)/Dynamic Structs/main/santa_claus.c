/**********************************************************************
 * @file   santa_claus.c                                              *
 * @author Vasileios Theodosiadis <vtheodos@ics.forth.gr>             *
 *                                                                    *
 * @brief  Main file for the needs of the Data Structures (HY-240a)   *
 * project (Fall 2015)                                                *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

#define LEN(x) (sizeof(x) / sizeof(*(x)))

char *tokens[128];
int asint[LEN(tokens)];
/*
int buy_present(int pid, int stock_cnt) {
	return 1;
}

int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {

	return 1;
}

int prepare_presents(void) {
	return 1;
}

int give_feedback(int cid, int s_degree) {
	return 1;
}

int analytics(void) {
	return 1;
}

int new_season(void) {
	return 1;
}

int clear_list_of_children(void) {
	return 1;
}

int search_present(int pid) {
	return 1;
}

int print_child(void) {
	return 1;
}

int print_district(void) {
	return 1;
}

int print_stock(void) {
	return 1;
}

int advanced_analytics(void) {
	return 1;
}
*/
void tokenize(char *s) { /*tokenization of input arguments*/
	char *p, *last;
	int i = 0;
	for ((p = strtok_r(s, " ", &last)); p;
	    (p = strtok_r(NULL, " ", &last))) {
		if (i < LEN(tokens) - 1) {
			tokens[i] = p;
			asint[i] = atoi(p);
			i++;
		}
	}
	tokens[i] = NULL;
}

int main(int argc, char *argv[]) { /*main function*/
	char *prog = argv[0];
	char *file = argv[1];
	char buf[1024];
	FILE *fp;
	int ret;
	char ev;

	if (file == NULL) {
		fprintf(stderr, "Usage: %s file\n", prog);
		return 1;
	}
    
    //fp = fopen("/Users/Keybraker/Desktop/C_files_for_Domes/test.txt", "r");
	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen %s: %s\n", file, strerror(errno));
		return 1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strcspn(buf, "\n")] = '\0';
		tokenize(buf);
		ev = *tokens[0];

		switch (ev) {
		case 'B':
			ret = buy_present(asint[1], asint[2]);
			break;
		case 'L':
			ret = letter_received(asint[1], asint[2], asint[3], asint[4], asint[5], asint[6]);
			break;
		case 'P':
			ret = prepare_presents();
			break;
		case 'F':
			ret = give_feedback(asint[1], asint[2]);
			break;
		case 'A':
			ret = analytics();
			break;
		case 'N':
			ret = new_season();
			break;
		case 'C':
			ret = clear_list_of_children();
			break;
		case 'S':
			ret = search_present(asint[1]);
			break;
		case 'H':
			ret = print_child();
			break;
		case 'I':
			ret = print_district();
			break;
		case 'T':
			ret = print_stock();
			break;
		case 'D':
			ret = advanced_analytics();
			break;
		default:
			fprintf(stderr, "Invalid event");
			return 1;
		}
		//fprintf(stderr, "Event '%c' %s\n", ev, ret ? "passed" : "failed");
	}
	return 1;
}

/*

Sample events:

B 20 10
B 30 15
B 40 20
B 10 5
B 11 5
B 12 5
B 13 5
B 14 5
L 10 2 3021 10 11 12
L 11 14 30231 10 11 12
L 15 1 30261 10 11 12
L 14 2 30271 10 11 12
L 100 4 30271 10 11 30
L 102 11 30271 20 30 40
L 112 11 30271 11 30 40
L 122 11 30271 11 30 40
L 127 14 30281 11 30 40
L 150 15 30241 11 30 40
L 151 15 30251 11 30 40
P
F 10 2
F 11 5
F 151 5
F 102 3
A
N
H
I
T
D
*/

/*I would like to thank the PhD candidates of the Department, who have been TAs of the course, Papaioannou Antonios and Zakkak Foivos for the provided material*/
