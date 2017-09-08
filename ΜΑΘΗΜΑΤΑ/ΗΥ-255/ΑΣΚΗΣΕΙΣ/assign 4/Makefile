#
# Makefile
# John Rambo
# rambo@csd.uoc.gr
# hy255
# as4
#

# the compiler to use
CC=gcc

# the options i'll pass
OFLAGS=-ansi -Wall -pedantic -o
CFLAGS=-ansi -Wall -pedantic -c

# system dependent
	REM=del#rm -f
	XF=.exe#.out

sudoku: grid.o sudoku.c
	$(CC) $(OFLAGS) sudoku$(XF) grid.o sudoku.c

grid.o: grid.c grid.h
	$(CC) $(CFLAGS) grid.c

clean:
	$(REM) *$(XF)
	$(REM) *.o
