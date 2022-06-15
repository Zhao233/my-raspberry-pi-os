#include "sched.h"
#include "printf.h"
#include "irq.h"
#include "list.h"
// current, init_task, task_list
static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &init_task;
//struct task_struct *task[NR_TASKS] = {&init_task, };

// tasks management
LIST_HEAD(tasks_list);

int nr_tasks = 1;

void sched_init(){
    INIT_LIST_HEAD(&init_task.head);

    list_add(&tasks_list, &init_task.head);
}

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
 * 2. the first for loop is tries to find the available task with maximum counter
 * 3. if not found a "next" task, the second for loop is to modify the counter in each task structure in the list 
 * */
void _schedule(void)
{
	preempt_disable();
	int c;

    struct list_head *_m_p_head = NULL;
	struct task_struct * _m_p_task = NULL;
    struct task_struct *next;

	while (1) {
		c = -1;
		next = 0;
		/**
        for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
        */


        list_for_each(_m_p_head, &tasks_list){
            _m_p_task = list_entry(_m_p_head, struct task_struct, head);
            
            if(_m_p_task && _m_p_task->state == TASK_RUNNING && _m_p_task -> counter > c){
                c = _m_p_task -> counter;
                next = _m_p_task;
            }
        }

		if (c) {
			break;
		}
        /**
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
        */

        list_for_each(_m_p_head, &tasks_list){
            _m_p_task = list_entry(_m_p_head, struct task_struct, head);
            
            if(_m_p_task){
                _m_p_task -> counter = (_m_p_task -> counter >> 1) + _m_p_task -> priority;
            }
        }
        
	}
	switch_to(next);
	preempt_enable();
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

void print_none(){
    printf("hhhh \n");
}
void test_print(unsigned long reg1, unsigned long reg2){
    printf("reg1: 0x%x, reg2: 0x%x\n", reg1, reg2);
}

void dump_task(struct task_struct *task){
    printf("task pid: %d, fp(x29): 0x%x, sp: 0x%x, pc(x30): 0x%x \n", task -> pid, task -> cpu_context.fp, task->cpu_context.sp, task -> cpu_context.pc);
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

    current -> counter = 0;

    // timer interrupt can be triggered during scheudle function
    enable_irq();
    _schedule();
    disable_irq();
}
