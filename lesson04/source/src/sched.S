#include "sched.h"

/*
 * switch cpu context from prev task to next task
 * x0: prev task's task_struct pointer(stack pointer), x1: next task's pointer
 * 1. save prev task's context to it's stack area
 * 2. recover next task's context
 */
.global cpu_context_switch
cpu_context_switch:
    mov x10, #THREAD_CPU_CONTEXT
    // x8: start address of cpu_context in prev task's task_struct
    add x8, x0, x10
    
    mov x9, sp

    stp x19, x20, [x8], #16
    stp x21, x22, [x8], #16
    stp x23, x24, [x8], #16
    stp x25, x26, [x8], #16
    stp x27, x28, [x8], #16
    // store operation's source register must be a interger register, so we can't save sp directly
    stp x29, x9 , [x8], #16
    str x30, [x8]

    add x8, x1, x10
    ldp x19, x20, [x8], #16
    ldp x21, x22, [x8], #16
    ldp x23, x24, [x8], #16
    ldp x25, x26, [x8], #16
    ldp x27, x28, [x8], #16
    ldp x9,  x29, [x8], #16
    ldr x30, [x8]

    mov x9, sp
    ret



