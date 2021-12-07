#include "arm/sysregs.h"
#include "mm.h"

.section ".text.boot"

.global _start
_start:
    mrs x0, mpidr_el1
    and x0, x0, #0xff
    cbz x0, master
    b proc_hang

proc_hang:
    b proc_hang

master:
    // 关闭地址翻译和cache
    ldr x0, =SCTLR_VALUE_BEFORE_KERNEL
    msr SCTLR_EL1, x0

    // 配置EL2
    ldr x0, =HCR_VALUE
    msr HCR_EL2, x0

    // 配置EL3
    ldr	x0, =SPSR_VALUE
	msr	SPSR_EL3, x0

    adr x0, el1_entry
    msr ELR_EL3, x0

    eret

el1_entry:
    // 清除bss段内容
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero

    // 设置栈指针
    mov sp, #LOW_MEMORY
    bl kernel_main
    // never reach
    b proc_hang