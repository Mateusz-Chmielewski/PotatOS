#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=246
struct systick
{
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};

// The base address of the SysTick register block is 0xE000 E010.
#define SYSTICK ((struct systick *)0xe000e010)

static volatile uint64_t s_ticks = 0;

void systick_init(uint32_t ticks);

void Systick_Handler(void);
uint64_t systick_get_ticks(void);
void delay(uint32_t ms);

#endif // SYSTICK_H