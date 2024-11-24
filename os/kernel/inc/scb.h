#ifndef SCB_DRIVER_H
#define SCB_DRIVER_H

#include <stdint.h>

#define SCB_BASE_ADDRESS 0xE000ED00

struct scb_t
{
  volatile uint32_t CPUID, ICSR, VTOR, AIRCR, SCR, CCR, SHPR1, SHPR2, SHPR3, SHCSR, CFSR, HFSR, MMAR, BFAR, AFSR;
};

#define SCB ((struct scb_t *)SCB_BASE_ADDRESS)

#define SCB_SHCSR_MEMFAULTENA BIT(16) // Usage fault enable bit
#define SCB_SHCSR_BUSFAULTENA BIT(17) // Bus fault enable bit
#define SCB_SHCSR_USGFAULTENA BIT(18) // Mem fault enable bit

#define SCB_ICSR_PENDSVSET BIT(28) // PendSV set-pending bit

#endif // SCB_DRIVER_H