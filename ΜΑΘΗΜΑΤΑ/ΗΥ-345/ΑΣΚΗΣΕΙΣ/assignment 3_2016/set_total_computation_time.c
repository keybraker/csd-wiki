#include <set_total_computation_time.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define __NR_set_total_computation_time_sys 342

int set_total_computation_time(int pid, unsigned int total_time)
{

	if (pid == -1)
	{
	}
	else if (pid > -1)
	{
		// psaksi na to vreis an oxi tote bges me EINVAL
	}
	else if (pid < -1)
	{
	}

	printf("set_total_computation_time started\n");

	if (syscall(__NR_set_total_computation_time_sys, 43) == -1)
	{
		fprintf(stderr, "set_total_computation_time failed, errno = %d\n", errno);
	}

	printf("set_total_computation_time ended\n");
}
