#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

// 
void timer_init(void)
{
    curVal = get32(TIMER_CL0);
    curVal += interval;
    put32(TIMER_C1, curVal);
}

void handle_timer_irq( void )
{   
    curVal += interval;
    // 设置下一个产生时钟中断的时刻
    put32(TIMER_C1, curVal);
    // 清除时钟状态，标志下一次到达产生时钟中断时，产生时钟中断
    put32(TIMER_CS, TIMER_CS_M1);

    printf("Timer interrupt received \n\r");
}
