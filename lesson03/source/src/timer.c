#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

void handle_timer_irq( void )
{   
    printf("Timer interrupt recieved! \n\r");
    gen_timer_reset();
    printf("timer reset \n\r");
} 

void generic_timer_init(){
    gen_timer_init();
    gen_timer_reset();
}

