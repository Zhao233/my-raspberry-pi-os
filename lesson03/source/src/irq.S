// 初始化异常向量表
.global irq_vector_init
irq_vector_init:
    adr x0, vectors
    msr vbar_el1, x0
    ret

.global enable_irq
enable_irq:
    msr daifclr, #2
    ret

.global diable_irq
diable_irq:
    msr daifset, #2
    ret
