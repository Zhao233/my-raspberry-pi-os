#include "printf.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"

void kernel_main(void) {
  uart_init();
  init_printf(0, putc);

  int el = get_el();
  
  irq_vector_init();
  generic_timer_init();
  enable_interrupt_controller();
  enable_irq();

  printf("current_el: %d \r\n", el);

  while (1) {
    uart_send(uart_recv());
  }
}
