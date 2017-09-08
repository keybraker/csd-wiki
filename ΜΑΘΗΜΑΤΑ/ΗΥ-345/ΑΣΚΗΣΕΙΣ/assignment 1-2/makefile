# build an executable named cs345_exec from cs345sh.c set_func.c unset_func.c printlvars_func.c cd_func.c
all: cs345sh.c cd_func.c set_func.c unset_func.c printlvars_func.c pipe_func.c
	gcc -g -Wall -o cs345_exec cs345sh.c cd_func.c set_func.c unset_func.c printlvars_func.c exec_func.c pipe_func.c echo_func.c man_func.c redirection_func_type_one.c redirection_func_type_two.c redirection_func_type_three.c

run:
	gcc -g -Wall -o cs345_exec cs345sh.c cd_func.c set_func.c unset_func.c printlvars_func.c exec_func.c pipe_func.c echo_func.c man_func.c redirection_func_type_one.c redirection_func_type_two.c redirection_func_type_three.c
	./cs345_exec
	$(RM) cs345_exec

clean: 
	$(RM) cs345_exec