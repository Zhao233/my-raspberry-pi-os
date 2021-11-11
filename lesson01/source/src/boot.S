#include "mm.h"

.section ".text.boot"

.global _start
_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xff
    cbz x0, master
    b proc_hang


proc_hang:
    b prog_hang

master:
    // 清楚bss段内容
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero

    // 设置栈指针
    mov sp, #LOW_MEMORY
    bl kernel_main
    // never reach
    b proc_hang
