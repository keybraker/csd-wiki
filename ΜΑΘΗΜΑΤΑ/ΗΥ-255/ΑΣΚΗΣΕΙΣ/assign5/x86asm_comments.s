# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# data section
N:	.long 1000	    # o arithmos 1000
S:	.long 0		    # o arithmos 0
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# instructions section
.globl main
main:	
	pushl %ebp	    # save old pointer
	movl %esp, %ebp	# move the contents of esp to ebp

 	# initialize
    movl N, %ebx	# move N address to ebx

 	# compute sum
L1:
	addl %ebx, S	# save add of ebx + S to ebx
	decl %ebx       # decrement counter
	cmpl $0, %ebx   # compare ebx with 0
	jng  L2	    	# jump to L2 if not greater
    movl $L1, %eax	# addr L1 to eax
    jmp *%eax   	# jump to address in eax

L2:
	# print result
	pushl S	    	# push long S
	pushl N	        # push long N
	pushl $Msg  	# push long msg address
	call printf 	# system call
	popl %eax   	# undo top, msg address
	popl %eax   	# undo top, N
	popl %eax   	# undo top, S

	# exit
	movl $0, %eax  	# move 0 address to eax
    leave	    	# esp <- ebp / ebp++ / free
 	ret             # return 0;
