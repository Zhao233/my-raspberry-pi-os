# 1 "src/sched.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "src/sched.c"
# 1 "include/sched.h" 1
# 1 "include/list.h" 1
# 1 "include/container_of.h" 1
# 2 "include/list.h" 2
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 143 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4

# 143 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 209 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 321 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef int wchar_t;
# 415 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 426 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 3 4
} max_align_t;
# 3 "include/list.h" 2
# 20 "include/list.h"

# 20 "include/list.h"
struct list_head{
    struct list_head *prev, *next;
};

static inline void __list_add(struct list_head *prev, struct list_head *new, struct list_head *next){
    prev -> next = new;
    new -> prev = prev;
    new -> next = next;
    next -> prev = new;
}

static inline void __list_del(struct list_head *prev, struct list_head *next){
    prev -> next = next;
    next -> prev = prev;
}

static inline void list_add(struct list_head *prev, struct list_head *new){
    __list_add(prev, new, new -> next);
}

static inline void list_del(struct list_head *head){
    __list_del(head -> prev, head -> next);

    head -> prev = 
# 43 "include/list.h" 3 4
                  ((void *)0)
# 43 "include/list.h"
                      ;
    head -> next = 
# 44 "include/list.h" 3 4
                  ((void *)0)
# 44 "include/list.h"
                      ;
}
# 2 "include/sched.h" 2
# 15 "include/sched.h"
extern struct task_struct *current;

extern struct list_head *tasks_head, *tasks_tail;
extern int nr_tasks;

struct cpu_context {

    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;

    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
};

struct task_struct {
    struct cpu_context cpu_context;
    long state;
    long counter;
    long priority;
    long preempt_counter;
    long pid;


    struct list_head head;
};

extern void sched_init(void);
extern void schedule(void);
extern void timer_tick(void);
extern void preempt_disable(void);
extern void preemt_enable(void);
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);
# 2 "src/sched.c" 2
# 1 "include/printf.h" 1
# 94 "include/printf.h"
# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 3 4

# 40 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 95 "include/printf.h" 2


# 96 "include/printf.h"
void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);
# 3 "src/sched.c" 2
# 1 "include/irq.h" 1



void enable_interrupt_controller( void );

void irq_vector_init( void );
void enable_irq( void );
void disable_irq( void );
# 4 "src/sched.c" 2
# 1 "include/list.h" 1

# 1 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h" 1 3 4
# 3 "include/list.h" 2
# 5 "src/sched.c" 2

static struct task_struct init_task = { {0,0,0,0,0,0,0,0,0,0,0,0,0}, 0,0,1,0 };
struct task_struct *current = &init_task;



struct list_head tasks_list = {&(tasks_list), &(tasks_list)};
struct list_head *tasks_head = &tasks_list;
struct list_head *tasks_tail = &tasks_list;

int nr_tasks = 1;

void sched_init(){
    list_add(tasks_tail, &init_task.head);
}

void preempt_disable(void)
{
    current -> preempt_counter++;
}

void preempt_enable(void)
{
    current -> preempt_counter--;
}







void _schedule(void)
{
 preempt_disable();
 int c;

    struct list_head *_m_p_head = 
# 42 "src/sched.c" 3 4
                                 ((void *)0)
# 42 "src/sched.c"
                                     ;
 struct task_struct * _m_p_task = 
# 43 "src/sched.c" 3 4
                                 ((void *)0)
# 43 "src/sched.c"
                                     ;
    struct task_struct *next;

 while (1) {
  c = -1;
  next = 0;
# 58 "src/sched.c"
        for((_m_p_head) = (tasks_head)->next; _m_p_head != tasks_head; _m_p_head = _m_p_head -> next){
            _m_p_task = ({ const typeof((struct task_struct *)0 -> head) *__mptr = (_m_p_head); (struct task_struct *) ((char*)__mptr - 
# 59 "src/sched.c" 3 4
                       __builtin_offsetof (
# 59 "src/sched.c"
                       struct task_struct
# 59 "src/sched.c" 3 4
                       , 
# 59 "src/sched.c"
                       head
# 59 "src/sched.c" 3 4
                       )
# 59 "src/sched.c"
                       ); });

            if(_m_p_task && _m_p_task->state == 0 && _m_p_task -> counter > c){
                c = _m_p_task -> counter;
                next = _m_p_task;
            }
        }

  if (c) {
   break;
  }
# 79 "src/sched.c"
        for((_m_p_head) = (tasks_head)->next; _m_p_head != tasks_head; _m_p_head = _m_p_head -> next){
            _m_p_task = ({ const typeof((struct task_struct *)0 -> head) *__mptr = (_m_p_head); (struct task_struct *) ((char*)__mptr - 
# 80 "src/sched.c" 3 4
                       __builtin_offsetof (
# 80 "src/sched.c"
                       struct task_struct
# 80 "src/sched.c" 3 4
                       , 
# 80 "src/sched.c"
                       head
# 80 "src/sched.c" 3 4
                       )
# 80 "src/sched.c"
                       ); });

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
 tfp_printf("entry schedule function \n");
    current -> counter = 0;

    _schedule();
}






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
# 129 "src/sched.c"
void timer_tick()
{
    current->counter--;

    if(current->counter > 0 || current -> preempt_counter > 0)
    {
        return;
    }

    current -> counter = 0;


    enable_irq();
    _schedule();
    disable_irq();
}
