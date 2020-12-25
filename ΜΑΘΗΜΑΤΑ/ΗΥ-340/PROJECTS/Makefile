all:
	clear
	bison --yacc --defines --verbose --output=Compiler_Exec/parser.c Alpha_Compiler/parser.y 
	flex --outfile=Compiler_Exec/scanner.c Alpha_Compiler/scanner.l Alpha_Compiler/flex/flex_functions/*.l
	gcc -o alphac Compiler_Exec/scanner.c Compiler_Exec/parser.c Alpha_Compiler/bison/bison_functions/*.c Alpha_Compiler/Intermediate/*.c Alpha_Compiler/TargetCode/*.c
	gcc -o alpha Virtual_Machine_Alpha/vm_Tools/*.c Virtual_Machine_Alpha/exec_Funcs/*.c -lm

example:
	clear
	bison --yacc --defines --verbose --output=Compiler_Exec/parser.c Alpha_Compiler/parser.y 
	flex --outfile=Compiler_Exec/scanner.c Alpha_Compiler/scanner.l Alpha_Compiler/flex/flex_functions/*.l
	gcc -o alphac Compiler_Exec/scanner.c Compiler_Exec/parser.c Alpha_Compiler/bison/bison_functions/*.c Alpha_Compiler/Intermediate/*.c Alpha_Compiler/TargetCode/*.c
	gcc -o alpha Virtual_Machine_Alpha/vm_Tools/*.c Virtual_Machine_Alpha/exec_Funcs/*.c -lm
	./alphac Compiler_Exec/examples/debug/debug.txt
	./alpha AlphaCode.bin
	
clean:
	rm Compiler_Exec/parser.c Compiler_Exec/scanner.c Compiler_Exec/parser.output Compiler_Exec/parser.h alphac alpha AlphaCode.bin
