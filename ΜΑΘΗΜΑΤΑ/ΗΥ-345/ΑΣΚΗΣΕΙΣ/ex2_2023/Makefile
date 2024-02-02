SRC = csd4140threads.c
CC = gcc 
CFLAGS = -g -pthread -o threads 

UNWANTED_FILES = $(filter-out $(SRC) Makefile README.txt, $(wildcard *))

all: threads

threads: $(SRC) 
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(UNWANTED_FILES)

.PHONY: all clean
