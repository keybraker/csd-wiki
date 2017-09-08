# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# data section
N:	.long 1000	    # number 1000
S:	.long 0		    # number 0
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# instructions section
.globl main
main:	
	pushl %ebp	    # save old base pointer
	movl %esp, %ebp	# make stack pointer the base pointer

 	# initialize
    movl N, %ebx	# move N addr in %ebx

 	# compute sum
L1:
	addl %ebx, S	# %ebx <- %ebx + S
	decl %ebx       # S-- (l)
	cmpl $0, %ebx   # compare %ebx with 0
	jng  L2	    	# jump to L2 if not greater than
    movl $L1, %eax	# %eax <- addr L1
    jmp *%eax   	# jump to addr in %eax

L2:
	# print result
	pushl S	    	# argument S
	pushl N	        # argument N
	pushl $Msg  	# argument Msg addr
	call printf 	# system call
	popl %eax   	# undo arg Msg addr
	popl %eax   	# undo arg N
	popl %eax   	# undo arg S

	# exit
	movl $0, %eax  	# %eax <- 0
    leave	    	# %esp <- %ebp; %ebp++; (l) free
 	ret             # return 0; from %eax

