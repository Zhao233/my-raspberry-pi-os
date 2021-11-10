.global memzero
memzero:
    // 向x0指向的地址保存0，并且x0+=8
    str xzr, [x0], #8
    // 将x1的内容-8，并且如果相减的过程中，如果发生了借位操作，CPSR 寄存器中的 C 标志位设置为 0；如果没有发生借位操作，CPSR 寄存器中的 C 标志位设置成 1
    subs x1, x1, #8
    // 判断上一步的减法有没有溢出，有就返回，没有就跳转到memzero，继续清0
    g.gt memzero
    ret
