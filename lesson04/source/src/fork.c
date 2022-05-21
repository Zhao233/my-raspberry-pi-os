#include "fork.h"
#include "sched.h"
#include "mm.h"
#include "entry.h"

/**
 * for a process: create a new process, this function must be executed with preemp disabled.
 * 1. copy current process state
 * 2. allocate specific stack frame
 * 3. set new process's pc to ret_from_fork
 * 4. add created process to tasks
 * 5. regulate global task counter
 * */

int copy_process(unsigned long fn, unsigned long arg)
{
    preempt_disable();
    struct task_struct *p;
    int pid;
    p = get_free_page();

    p -> state = TASK_RUNNING;
    p -> priority = current -> priority;
    p -> counter = p -> counter;
    p -> preempt_counter = 1;

    p -> cpu_context.x19 = fn;
    p -> cpu_context.x20 = arg;
    p -> cpu_context.pc = (unsigned long)ret_from_fork;
    p -> cpu_context.sp = (unsigned long)p + THREAD_SIZE;
    
    pid = nr_tasks++;

    p -> pid = pid;

    task[nr_tasks] = p;
    
    preempt_enable();

    return 0;
}
