#include "systick.h"
#include "rcc.h"
#include "scb.h"
#include "task.h"
#include <stdint.h>

#include "task.h"

static volatile uint64_t s_ticks = 0;

void systick_init(uint32_t ticks) {
  if ((ticks - 1) > 0xffffff)
    return;                  // Systick timer is 24 bit
  SYSTICK->LOAD = ticks - 1; // Set reload register
  SYSTICK->VAL = 0;          // Clear current value
  SYSTICK->CTRL |= SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT |
                   SYSTICK_CTRL_CLKSOURCE; // Enable systick
  rcc_syscfg_enable();                     // Enable clock for SYSTICK
}

void sys_tick_handler(void) {
  s_ticks++;

  osCheckBlockedTasks(); // check if any task is blocked and if it is time to
                         // unblock it

  SCB->ICSR |= SCB_ICSR_PENDSVSET; // trigger PendSV exception
}

uint64_t systick_get_ticks(void) { return s_ticks; }
