#ifndef SCB_DRIVER_H
#define SCB_DRIVER_H

#include "common.h"
#include <stdint.h>

#define SCB_BASE_ADDRESS 0xE000ED00

/*
System control block

The System control block (SCB) provides system implementation information, and
system control. This includes configuration, control, and reporting of the
system exceptions.

https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=221
 */

typedef struct Scb {
  volatile uint32_t CPUID, ICSR, VTOR, AIRCR, SCR, CCR, SHPR1, SHPR2, SHPR3,
      SHCSR, CFSR, HFSR, MMAR, BFAR, AFSR;
} Scb;

#define SCB ((Scb *)SCB_BASE_ADDRESS)

#define SCB_SHCSR_MEMFAULTENA BIT(16) // Usage fault enable bit
#define SCB_SHCSR_BUSFAULTENA BIT(17) // Bus fault enable bit
#define SCB_SHCSR_USGFAULTENA BIT(18) // Mem fault enable bit

#define SCB_ICSR_PENDSVSET BIT(28) // PendSV set-pending bit

#endif // SCB_DRIVER_H