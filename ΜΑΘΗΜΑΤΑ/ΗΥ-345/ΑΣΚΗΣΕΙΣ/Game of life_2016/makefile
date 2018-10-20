# build an executable named cs345_exec from cs345sh.c set_func.c unset_func.c printlvars_func.c cd_func.c
all:
	gcc -g -Wall -o game_of_life_exec game_of_life.c file_reader.c exec_ten_partition.c print_life.c

run:
	gcc -g -Wall -pthread -o game_of_life_exec game_of_life.c file_reader.c exec_ten_partition.c print_life.c

	./game_of_life_exec

	$(RM) game_of_life_exec

clean:
	$(RM) game_of_life_exec
