#include "mini_uart.h"

void kernel_main(unsigned long long processor_id){
    
    if(processor_id == 0){
        uart_init();
        uart_send_string("Hello world! zx's kernel! \n");

    }

    uart_send_string("it's proceesor: " + processor_id);
    uart_send_string("\n\n");

    // hang all processor
    while(1){
        //uart_send(uart_recv());
    }
}
