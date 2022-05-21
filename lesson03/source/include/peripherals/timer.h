#ifndefaifndef _P_TIMER_H

#define _P_TIMER_H

#include "peripherals/base.h"

#define INTERVAL_TIMER 38461538

#ifdef SYSTEM_TIMER
    #define P_TIMER_BASE (PBASE+0x00003000)

    #define TIMER_CS        (P_TIMER_BASE+0x0)
    #define TIMER_CLO       (P_TIMER_BASE+0x4)
    #define TIMER_CHI       (P_TIMER_BASE+0x8)
    #define TIMER_C0        (P_TIMER_BASE+0xC)
    #define TIMER_C1        (P_TIMER_BASE+0x10)
    #define TIMER_C2        (P_TIMER_BASE+0x14)
    #define TIMER_C3        (P_TIMER_BASE+0x18)

    //
    #define TIMER_CS_M0 (1 << 0)
    #define TIMER_CS_M1 (1 << 1)
    #define TIMER_CS_M2 (1 << 2)
    #define TIMER_CS_M3 (1 << 3)
#endif

#ifdef GENERIC_TIMER
    #define ENABLE_TIMER 1
    #define IMASK_TIMER 
    #define ISTATUS_TIMER
#endif

#endif
