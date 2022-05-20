#ifndef _SCHED_H

#define THREAD_CPU_CONTEXT_INDEX    0
#ifndef __ASSEMBLER__
#define THREAD_SIZE                 4096

#define NR_TASKS                    64

#define FIRST_TASK                  task[0]
#define LAST_TASK                   task[NR_TASK-1]

#define TASK_RUNNING                0

extern struct task_struct           *current;
extern struct task_struct           *task[NR_TASKS];
extern int    nr_tasks;

struct cpu_context {
    // calle-save reg
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    // stack frame reg, stack pointer reg, link reg 
    unsigned long fp; // x29
    unsigned long sp;
    unsigned long pc; // x30 lr
}

struct task_struct {
    struct cpu_context cpu_context;
    long state;
    long counter; 
    long priority;
    long preempt_count;
}

extern void sched_init(void);
extern void schedule(void);
extern void timer_tick(void);
extern void preempt_disable(void);
extern void preemt_enable(void);
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);

#define INIT_TASK \
/*cpu_context*/ {{0,0,0,0,0,0,0,0,0,0,0,0,0,0},}\
/*state*/ \0, 0, 1 0\
}
#endif
#endif
