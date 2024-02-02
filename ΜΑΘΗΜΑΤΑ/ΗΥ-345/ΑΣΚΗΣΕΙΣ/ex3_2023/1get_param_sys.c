#include <linux/kernel.h>
#include <asm/current.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include "d_params.h"

asmlinkage long sys_get_param_sys(struct d_params * params) {

    struct task_struct *task = get_current();

    printk("CSD4140 | ANTONIA KRASOUDAKI\n");
    printk("Called get_param_sys \n");


    if (copy_to_user(&(params->member_id), &(task->member_id) , sizeof(int))) {
        printk("Error getting member id\n");
        return -EINVAL;  
    }

    if (copy_to_user(&(params->group_name), &(task->group_name) , sizeof(char) ) ) {
        printk("Error getting group name\n");
        return -EINVAL;  
    }

    printk("Get param success\n");    
        return 0;

}
