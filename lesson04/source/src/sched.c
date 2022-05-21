#include "sched.h"
#include "printf.h"
#include "irq.h"

// current, init_task, task_list
static task_struct init_task = &INIT_TASK;
struct task_struct *current = &init_task;
struct task_struct *task[NR_TASKS] = {&init_task, };

int nr_tasks = 1;

void preempt_disable(void)
{
    current -> preempt_counter++;
}

void preempt_enable(void)
{
    current -> preempt_counter--;
}

/**
 * pre-process before cpu_switch_to
 * set current = next
 * switch cpu context
 * */
void switch_to(struct task_struct *next)
{
   if(current == next){
        return ;
   } 

   struct task_struct *prev = current;
   
   current = next;
   
   cpu_switch_to(prev, next);
}


/**
 * when timer interrupt arrive, call this function.
 * 1. decrese current task's counter
 * 2. determin whether current task can be scheduled by check counter(if counter equals 0, means current task can be scheduled) and preempt_counter(if preempt_counter > 0 represent the preempt is disabled)
 * 3. set current task's state(not in task struct) to 'can be scheduled'
 * 4. call schedule function
 * */
void timer_tick()
{
    current->counter--;

    if(current->counter > 0 || current -> preempt_counter > 0)
    {
        return;
    }

    curren -> counter = 0;

    // timer interrupt can be triggered during scheudle function
    enable_irq();
    _schedule();
    disable_irq();
}
