#include "sched.h"
#include "printf.h"
#include "irq.h"

// current, init_task, task_list
static task_struct init_task = &INIT_TASK;
struct task_struct *current = &init_task;
struct task_struct *task[NR_TASKS] = {&init_task, };

int nr_tasks;

//
