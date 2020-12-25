#include "constTables.h"

void make_operand 					(expr* e, vmarg* arg);
void make_numberOperand				(vmarg* arg, double val);
void make_boolOperand 				(vmarg* arg, unsigned int val);
void make_retvalOperand 			(vmarg* arg);

void EXPANDER_IJ					(void);
void add_incomplete_jump			(unsigned int instrNo, unsigned int taddress);
void patchInstrLabel				(unsigned int instrNo, unsigned int taddress);
void patchIncompleteJumps			(unsigned int totalQuads);

void make_booloperand 				(vmarg *arg, unsigned int logical);
void reset_operand 					(vmarg *arg);
void make_retvaloperand 			(vmarg *arg);
void setArgsNull					(instruction* t);
void generateTcode					(unsigned int totalQuads);

void generate						(vmopcode op, quad *quadInput);
void generate_ADD 					(quad *quadInput);
void generate_SUB 					(quad *quadInput);
void generate_MUL 					(quad *quadInput);
void generate_DIV 					(quad *quadInput);
void generate_MOD 					(quad *quadInput);
void generate_NEWTABLE 				(quad *quadInput);
void generate_TABLEGETELM 			(quad *quadInput);
void generate_TABLESETELEM			(quad *quadInput);
void generate_ASSIGN 				(quad *quadInput);
void generate_NOP 					(quad *quadInput);

void generate_JUMP 					(quad *quadInput);
void generate_IF_EQ 				(quad *quadInput);
void generate_IF_NOTEQ 				(quad *quadInput);
void generate_IF_GREATER 			(quad *quadInput);
void generate_IF_GREATEREQ 			(quad *quadInput);
void generate_IF_LESS 				(quad *quadInput);
void generate_IF_LESSEQ 			(quad *quadInput);

unsigned int nextinstructionlabel	(void);
unsigned int currprocessedquad		(void);

typedef void (*generator_func_t) (quad*);
typedef struct incomplete_jump incomplete_jump;

struct incomplete_jump {

	unsigned int instrNo;
	unsigned int iaddress;

};

extern incomplete_jump* ij_head ;
extern unsigned int ij_total ;
