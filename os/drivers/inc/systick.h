#ifndef SYSTICK_H
#define SYSTICK_H

#include "common.h"
#include "memorymap.h"
#include <stdint.h>

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=246
struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};

// The base address of the SysTick register block is 0xE000 E010.
#define SYSTICK ((struct systick *)SYSTICK_BASE)

#define SYSTICK_CTRL_ENABLE BIT(0)  // enables counter
#define SYSTICK_CTRL_TICKINT BIT(1) // enables interrupt
#define SYSTICK_CTRL_CLKSOURCE                                                 \
  BIT(2) // clock source selection (0: external, 1: processor clock)

void systick_init(uint32_t ticks);

// FREQ/1000 - Tick every 1 ms so s_ticks will be incremented every 1 ms
// 1 second = 1000 ms, so 1000 ms / 1 ms = 1000 ticks
void sys_tick_handler(void);
uint64_t systick_get_ticks(void);

#endif // SYSTICK_H
