#include "../vm_Tools/phase5.h"

#define a_c_r "\x1b[31m"
#define a_c_g "\x1b[32m"
#define a_c_y "\x1b[33m"
#define a_c_b "\x1b[34m"
#define a_c_m "\x1b[35m"
#define a_c_c "\x1b[36m"
#define a_c_re "\x1b[0m"
#define under "\e[4m"
#define under_re "\e[0m"
#define italic "\e[3m"
#define italic_re "\e[0m"
#define bold "\e[1m"
#define bold_re "\e[0m"

void execute_cycle(void);

typedef void (*execute_func_t)(instruction *);
#define AVM_MAX_INSTRUCTIONS 20

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_comparison
#define execute_jge execute_comparison
#define execute_jgt execute_comparison
#define execute_jlt execute_comparison

void execute_add(instruction *instr);
void execute_sub(instruction *instr);
void execute_mul(instruction *instr);
void execute_div(instruction *instr);
void execute_mod(instruction *instr);
void execute_assign(instruction *instr);
void execute_call(instruction *instr);
void execute_pusharg(instruction *instr);
void execute_funcenter(instruction *instr);
void execute_funcexit(instruction *instr);
void execute_jeq(instruction *instr);
void execute_jne(instruction *instr);
void execute_jle(instruction *instr);
void execute_jge(instruction *instr);
void execute_jlt(instruction *instr);
void execute_jgt(instruction *instr);
void execute_newtable(instruction *instr);
void execute_tablegetelem(instruction *instr);
void execute_tablesetelem(instruction *instr);
void execute_nop(instruction *instr);
void execute_jump(instruction *instr);

void execute_arithmetic(instruction *instr);

void execute_comparison(instruction *instr);