#
# Makefile
# John Rambo
# rambo@csd.uoc.gr
# hy255
# as6
#

# the compiler to use
CC=gcc

# the options i'll pass
OFLAGS=-ansi -Wall -pedantic -o
CFLAGS=-ansi -Wall -pedantic -c

# system dependent
	REM=rm -f
	XF=.out
	RUN=./


all: data3 data6 data9

data3: createdata3.o
	$(CC) $(OFLAGS) createdata3$(XF) createdata3.o
	$(RUN)createdata3$(XF) > data3.in

data6: createdata6.o
	$(CC) $(OFLAGS) createdata6$(XF) createdata6.o
	$(RUN)createdata6$(XF) > data6.in

data9: createdata9.o
	$(CC) $(OFLAGS) createdata9$(XF) createdata9.o
	$(RUN)createdata9$(XF) > data9.in

createdata3.o: createdata3.c
	$(CC) $(CFLAGS) createdata3.c

createdata6.o: createdata6.c
	$(CC) $(CFLAGS) createdata6.c

createdata9.o: createdata9.c
	$(CC) $(CFLAGS) createdata9.c

clean:
	$(REM) *$(XF)
	$(REM) *.o
	$(REM) *.in

