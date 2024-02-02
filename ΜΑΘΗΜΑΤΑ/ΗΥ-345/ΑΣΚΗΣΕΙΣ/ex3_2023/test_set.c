#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define __NR_set_param_sys 343

int main()
{
    char group_name = 'B';
    int member_id = 1;
    char group_name1 = 'C';
    int member_id1 = 12;
    char group_name2 = 'd';
    int member_id2 = -1;
    char group_name3 = 'A';
    int member_id3 = 3;

    printf("Arguments passed: %d , %c\n\n", member_id, group_name);

    printf("Trap to kernel level \n");

    long ret = syscall(__NR_set_param_sys, group_name, member_id);

    if (ret == 0)
    {
        printf("Parameters set successfully.\n");
    }
    else
    {
        printf("Error setting parameters\n");
    }

    printf("Back to user level \n\n");

    printf("Arguments passed: %d , %c\n\n", member_id1, group_name1);

    printf("Trap to kernel level \n");

    long ret1 = syscall(__NR_set_param_sys, group_name1, member_id1);

    if (ret1 == 0)
    {
        printf("Parameters set successfully.\n");
    }
    else
    {
        printf("Error setting parameters\n");
    }

    printf("Back to user level \n\n");

    printf("Arguments passed: %d , %c\n\n", member_id2, group_name2);

    printf("Trap to kernel level \n");

    long ret2 = syscall(__NR_set_param_sys, group_name2, member_id2);

    if (ret2 == 0)
    {
        printf("Parameters set successfully.\n");
    }
    else
    {
        printf("Error setting parameters\n");
    }

    printf("Back to user level \n\n");

    printf("Arguments passed: %d , %c\n\n", member_id, group_name);

    printf("Trap to kernel level \n");

    long ret3 = syscall(__NR_set_param_sys, group_name, member_id);

    if (ret3 == 0)
    {
        printf("Parameters set successfully.\n");
    }
    else
    {
        printf("Error setting parameters\n");
    }

    printf("Back to user level \n\n");

    return 0;
}