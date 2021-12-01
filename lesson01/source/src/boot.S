#include "mm.h"

.section ".text.boot"

.global _start
_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xff
    mov x1, x0
    cbnz x0, _init_no_master
    bl init_bss
_init_no_master:
    b master

proc_hang:
    b proc_hang

init_bss:
    // 清除bss段内容
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero

init_stack:
    // x0 save the current processor id
    // stack start at: LOW_MEMORY + <processor_id> * 2k
    mov x1, #0x4000
    mul x0, x0, x1
    mov x1, #LOW_MEMORY
    add x0, x0, x1
    mov sp, x1

master:
    // initialize the stack space
    mov x1, x0
    mov x2, #1000
    mul x0, x2, x2
    bl delay
    mov x0, x1
    bl init_stack

    bl kernel_main
    // never reach
    b proc_hang
