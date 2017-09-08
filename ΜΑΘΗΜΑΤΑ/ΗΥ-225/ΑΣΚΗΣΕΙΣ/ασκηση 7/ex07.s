#ALEXANDROS MARANTOS 3329
#HY 225 SEIRA ASKHSEWN 7

		.data
mhnyma:	.asciiz "Give a positive integer: "
nl:		.asciiz "\n"
		.text
		.globl main
		.globl loop

main:
		
		jal node_alloc

		sw $0, 0($v0)			#initialize data = 0
		sw $0, 4($v0)			#initialize nxtptr = 0

		addi	$s0,$v0,0			#s0 arxi listas
		addi	$s1,$v0,0			

loop_a:
		jal read_int			#read int
		
		addi $s2,$v0,0			#save int
		
		jal node_alloc

		sw 	$s2, 0($v0)			#store int to data
		sw	$v0, 4($s1)			#new v0 to old s1
		addi	$s1, $v0, 0		#initialize s1 the new v0
		
		j loop_a

read_int:
		addi	$v0, $0, 4			#print
		la		$4, mhnyma
		syscall

		addi 	$v0, $0, 4		#print string system call
		la		$4, nl			#print nl
		syscall
		
		addi $v0, $0, 5			#read int
		syscall

		jr	$ra

node_alloc:
		
		addi $v0, $0, 9			#set break
		addi $a0, $0, 8
		syscall

		jr $ra				#return

#telos a merous, mexri edw swsto


#read_int_compare:

#		addi 	$2,$0,4				#print string system call
#		la		$4,nl				#print nl
#		syscall
		
#		jal		read _int
		
#		addi	$
#loop_b:

#		addi	$a0, $2, 0		#take the int(s2) as argument
#		lw		$t1,4($s2)		#deixnei ston epomeno komvo
#		addi	$s2, $t1, 0 	#to metaferw ston saved s2
		
#		jal		print_node
		
#		j loob_b
		

#print_node:

#		lw		$t0, ($a0)			#pernao se temp ton int
#		slt		$t1, $t0, $s1		#check if t0<s1
#		beq		$t1, $0, label
		
#		addi    $2,$0,1        		#print integer system call
#       add     $a0,$t0,$0     		#a0 integer to be printed            
#       syscall

#		addi 	$2,$0,4				#print string system call
#		la		$4,nl				#print nl
#		syscall
		
#label:

#		jr	$ra					#epistrefei thn dieythynsi

		j main