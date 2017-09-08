#include <stdio.h> 
#include <stdlib.h> 

#define N 1000

int i = N;
int S = 0;

int main (void) 
{

  /* while (n >= 0) { Sum += n; n--;} */
  asm(
	"movl i, %ebx\n"
"L1:\n\t"
	"addl %ebx, S\n\t"
	"decl %ebx;"
	"cmpl $0, %ebx\n\t"
	"jng  L2\n\t"
        "movl $L1, %eax\n\t"
        "jmp *%eax\n"
"L2:"
  );

  printf("The sum from 0 to %d is %d\n", N, S);

  return 0;
}

