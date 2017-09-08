/*ALEXANDROS MARANTOS
	3329
HY 255 ASSIGNMENT 5*/

1)Gia to programma x86asm.s

	(a)// ektelw tin entoli: gcc -o x86asm x86asm.s ,kai typwnei:
	   The sum from 0 to 1000 is 500500

	(b)// sto arxeio x86asm_comments.s

	(c)// ektelw  tin entoli: gcc -g -o x86asm x86asm.s
	   // gdb x86asm
	   // (gdb) run

	(d)O katallilos arithmos entolon einai 19 giati sthn 19i entoli kanei return
	   //ara: x/19i *main

	   O arithmos tis main se bytes einai 60

	   To offset einai 28

	(e)
		(i) S = 500500
		(*S) = 0x8049668
		(*Msg) = 0x804966c

		(ii) The sum from 0 to 1000 is 99

2)Gia to programma sum.c
	(a)
	The sum from 0 to 1000 is 500500

	(b)
	Oi entoles assembly tis main einai 30

	(d)
	O arithmos ton entolon tis main einai 30

	Ta bytes pou katalamvanoun einai 77

	Katallhlo offset gia to breakpoint einai to 13

	(e)
	(gdb) p Sum
	$1 = 500500
	(gdb) p &Sum
	$2 = (int *) 0x8049704 <Sum>
	(gdb) p n
	$3 = -1
	(gdb) p &n
	$4 = (int *) 0x80496fc <n>

	to programma typwnei:
	The sum from 0 to 1000 is 98

	The sum from 0 to 1000 is 99

	(f)
	The sum from 0 to 1000 is 495450

3)
	(a)
	To programma typwnei:
	The sum from 0 to 1000 is 500500

	(b)
	H main exei 24 entoles assembly

	(c)
	The sum from 0 to 1000 is 500500





