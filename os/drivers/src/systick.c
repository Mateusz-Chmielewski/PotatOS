#include "systick.h"
#include "rcc.h"
#include <stdint.h>
#include "common.h"

void systick_init(uint32_t ticks)
{
  if ((ticks - 1) > 0xffffff)
    return;                                                                            // Systick timer is 24 bit
  SYSTICK->LOAD = ticks - 1;                                                           // Set reload register
  SYSTICK->VAL = 0;                                                                    // Clear current value
  SYSTICK->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE; // Enable systick
  rcc_syscfg_enable();                                                                 // Enable clock for SYSTICK
}

void sys_tick_handler(void)
{
  s_ticks++;
}

uint64_t systick_get_ticks(void)
{
  return s_ticks;
}

void delay(uint32_t ms)
{
  uint32_t until = s_ticks + ms; // Time in a future when we need to stop
  while (s_ticks < until)
    (void)0;
}