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
 * schedule main function, select the next task that needs to run. preempt must be disbale during schedule
 * 1. iterate all task
 * */
static void _schedule()
{
void _schedule(void)
{
	preempt_disable();
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	switch_to(task[next]);
	preempt_enable();
}
}

void schedule(void)
{
    current -> counter = 0;

    _schedule();
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

void schedule_tail(void) {
	preempt_enable();
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
