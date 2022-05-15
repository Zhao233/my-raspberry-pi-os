#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "entry.h"
#include "peripherals/irq.h"

const char *entry_error_message[] = {
    "SYNC_INVALID_EL1t",
    "IRQ_INVALID_EL1t",
    "FIQ_INVALID_EL1t",
    "ERROR_INVALID_EL1T",

    "SYNC_INVALID_EL1h",
    "IRQ_INVALID_EL1h",
    "FIQ_INVALID_EL1h",
    "ERROR_INVALID_EL1h",

    "SYNC_INVALID_EL0_64",
    "IRQ_INVALID_EL0_64",
    "FIQ_INVALID_EL0_64",
    "ERROR_INVALID_EL0_64",

    "SYNC_INVALID_EL0_32",
    "IRQ_INVALID_EL0_32",
    "FIQ_INVALID_EL0_32",
    "ERROR_INVALID_EL0_32"
};

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
    printf("%s, ESR: %x, address", entry_error_message[type], esr, address);
}


void enable_interrupt_controller()
{
    put32(TIMER_INT_CTRL_0, TIMER_INT_CTRL_0_VALUE);

}

// the entry of the irq
void handle_irq(void)
{
    unsigned int irq = get32(INT_SOURCE_0);
    printf("enter the handle_irq_function, irq: %d \n\r", irq);
    switch(irq){
        case (GENERIC_TIMER_INTERRUPT):
            handle_timer_irq();
            break;

        default:
            printf("Unknown pending irq: %x\r\n", irq);
    }
}
