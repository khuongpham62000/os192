#ifndef _PROC_MEM_H_
#define _PROC_MEM_H_
#include <unistd.h>

struct proc_segs {
unsigned long mssv;
unsigned long start_code;
unsigned long end_code;
unsigned long start_data;
unsigned long end_data;
unsigned long start_heap;
unsigned long end_heap;
unsigned long start_stack;
};
static void locate_mem(struct task_struct *task, struct proc_segs * info);
long procmem(pid_t pid, struct prog_segs *info);
#endif // _PROC_MEM_H_