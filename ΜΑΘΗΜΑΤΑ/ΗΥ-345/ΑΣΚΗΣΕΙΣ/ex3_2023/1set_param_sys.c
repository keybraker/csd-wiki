#include <linux/kernel.h>
#include <asm/current.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

asmlinkage long sys_set_param_sys(char arg0, int arg1) {
    struct task_struct *task =  get_current();

    printk("CSD4140 | ANTONIA KRASOUDAKI\n");
    printk("Called set_sys with arguments: %c  ,  %d\n", arg0 , arg1);

    if ( ( arg0 >= 'A' && arg0 <= 'Z' ) && (arg1 > 0) ) {
        printk("PARAMS SET CORRECTLY\n");
	task->group_name = arg0;
        task->member_id = arg1;
	printk("Task member_id in set param syscall is: %d\n", task->member_id);
        printk("Task group_name in set param syscall is: %c\n", task->group_name);
        return 0;

    }else{
        printk("PARAMS ERROR RETURN EINVAL\n");
        return -EINVAL;
    }

}
