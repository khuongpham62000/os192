#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>

static int pid_mem = 1;

static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
        int count = 0;
        mm = task->mm;
        mm->start_code;
        mm->end_code;
        mm->start_data;
        mm->end_data;
        mm->start_brk;
        mm->brk;
        mm->start_stack;
}

static int mm_exp_load(void){
        struct task_struct *task;
        printk("\nGot the process id to look up as %d.\n", pid_mem);
        for_each_process(task) {
                if ( task->pid == pid_mem) {
                        printk("%s[%d]\n", task->comm, task->pid);
                        print_mem(task);
                }
        }
        return 0;
}

static void mm_exp_unload(void)
{
        printk("\nPrint segment information module exiting.\n");
}

module_init(mm_exp_load);
module_exit(mm_exp_unload);
module_param(pid_mem, int, 0);

MODULE_AUTHOR ("Krishnakumar. R, rkrishnakumar@gmail.com");
MODULE_DESCRIPTION ("Print segment information");
MODULE_LICENSE("GPL");