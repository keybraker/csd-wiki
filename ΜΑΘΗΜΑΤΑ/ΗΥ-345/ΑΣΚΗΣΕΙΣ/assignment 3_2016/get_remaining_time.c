#include <set_total_computation_time.h>

#define __NR_set_get_remaining_time_sys 343

int get_remaining_time(int pid, struct t_params *t_arguments)
{

	printf("get_remaining_time started\n");

	if (syscall(__NR_get_remaining_time_sys, 44) == -1)
	{
		fprintf(stderr, "get_remaining_time failed, errno = %d\n", errno);
	}

	printf("get_remaining_time ended\n");
}
