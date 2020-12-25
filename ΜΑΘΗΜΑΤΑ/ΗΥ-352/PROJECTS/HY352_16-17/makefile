# build an executable named JSON 

CC=g++ 
CFLAGS=-std=c++11

all: JSON

JSON:	json_code.cpp
	$(CC) $(CFLAGS) json_code.cpp -o JSON
	clear

clean:
	rm -rf *o JSON
	clear

run:	json_code.cpp
	$(CC) $(CFLAGS) json_code.cpp -o JSON
	./JSON
	rm -rf *o JSON
