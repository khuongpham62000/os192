#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>

static void locate_mem(struct task_struct *task, struct proc_segs * info)
{
        struct mm_struct *mm;
        int count = 0;
        mm = task->mm;
        info->start_code  = mm->start_code;
        info->end_code    = mm->end_code;
        info->start_data  = mm->start_data;
        info->end_data    = mm->end_data;
        info->start_heap  = mm->start_brk;
        info->end_heap    = mm->brk;
        info->start_stack = mm->start_stack;
}

long procmem(pid_t pid, struct proc_segs * info) {
    struct task_struct *task;
    info->mssv = 1812694;
    for_each_process(task){
        if ( task->pid == pid) {
            printk("%s[%d]\n", task->comm, task->pid);
            locate_mem(task, info);
        }
    }
    return 0;
}