# ALEXANDROS MARANTOS 3329

		.data
mhnyma:	.asciiz "Give an integer: "
nl:		.asciiz "\n"	
array:	.space 32			 	# megethos array 32 bits
		.align 2				# 4 bits kathe stoixeio
		
		.text
		.globl main
		.globl loop
		.globl loop_1

main:
		la      $s0, 0		  # initialize first counter
		la      $s1, 8      # initialize first elegxos
		la      $s2, 0 	  # initialize stoixeio array a loop
		la      $s3, 0		  # initialize second counter
		la      $s4, 8	  # initialize second elegxos 	
		la      $s5, 28	  # initialize stoixeio1
		la	   $v1, 6		  # initialize multiplier


loop:
		addi	$2, $0, 4		 # ektypwsi
		la		$4,mhnyma
		syscall
		 
		addi	$2, $0, 4
		la		$4, nl
		syscall
		
		addi	$2, $0, 5		 # diavasma int
		syscall

		
		sw      $2, array($s2) 	 # array[i] = s2
		
		addi    $s0, $s0, 1	    	# auxisi counter kata 1
		addi    $s2, $s2, 4	  # auxisi stoixeioy kata 4
 		
		bne     $s0, $s1, loop 	# while(s0 != 8)

		addi	$2, $0, 4		 # new line (\n)
		la		$4, nl
		syscall

loop_1:
		lw 	$15, array($s5)  # array[i] = s5
		
		mult	$15, $v1		 # multiply
		mflo	$15				 # pairnei ls-32-bits
		
		addi 	$2, $0, 1			 # print	
		add 	$4, $15, $0		 
		syscall
		
		addi	$2, $0, 4
		la		$4, nl		 # \n
		syscall
		
		addi	$s3, $s3, 1	 	 # auxisi counter kata 1
		addi	$s5, $s5, -4	 # meiwsi stoixeiou kata 4 bytes
		
		bne 	$s3, $s4, loop_1 # while(s3 != 8)
		
		addi	$2, $0, 4
		la		$4, nl			 # new line (\n)
		syscall
		
		j main
