.global put32
put32:
    str w1, [x0]
    ret

.global get32
get32:
    ldr w0, [x0]
    ret

// 延时函数，递减到一返回
.global delay
delay:
    subs x0, x0, #1
    // x0 不等于1，跳转到delay函数
    bne delay
    ret