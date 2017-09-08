# MARANTOS ALEXANDROS 3329

CFLAGS=-ansi -Wall -pedantic
symtablehash.o: symtable.h symtablehash.c
		gcc -c symtablehash.c

symtablelist.o: symtable.h symtablelist.c
		gcc -c symtablelist.c

list: symtable.h symtablelist.o
	gcc $(CFLAGS) -o testsymtab testsymtab.c symtablelist.o

hashtable: symtable.h symtablehash.o
	  gcc $(CFLAGS) -o testsymtab testsymtab.c symtablehash.o


clean:
	rm -rf *.o
	rm -rf testsymtab
