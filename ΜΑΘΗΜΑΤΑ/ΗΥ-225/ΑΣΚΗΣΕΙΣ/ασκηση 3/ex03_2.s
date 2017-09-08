		.data
info: 	.asciiz "xyz"
		
		.text
		.globl main
		
main:		
		lw 		$19,info($16) 	  #initialize register $19	
		li 		$v0, 1		  # load appropriate system call code into register $v0;
							  # code for printing integer is 1
		move	$a0, $19
		syscall