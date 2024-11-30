#ifndef CONTROL_H
#define CONTROL_H

#include "common.h"
#include <stdint.h>

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=17&zoom=100,165,556
// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=25&zoom=100,165,556
typedef enum {
  CONTROL_PRIVILEGED = 0,  // privileged mode
  CONTROL_UNPRIVILEGED = 1 // unprivileged mode
} CONTROL_PrivilegeLevel;

typedef enum {
  CONTROL_STACK_MSP = 0, // use main stack pointer (MSP)
  CONTROL_STACK_PSP = 1  // use process stack pointer (PSP)
} CONTROL_StackPointer;

typedef enum {
  CONTROL_FP_DISABLED = 0, // floating point unit disabled
  CONTROL_FP_ENABLED = 1   // floating point unit enabled
} CONTROL_FloatingPoint;

#define CONTROL_nPRIV BIT(0) // privileged mode
#define CONTROL_SPSEL BIT(1) // stack pointer selection
#define CONTROL_FPCA BIT(2)  // floating point context active

static inline void __set__CONTROL(uint32_t control) {

  __asm volatile(
      "MSR CONTROL, %0" // Move the value into the CONTROL register
      :                 // No outputs
      : "r"(control)    // Input: the value to be set in the CONTROL register
  );
}

uint32_t __get_CONTROL(void) {
  uint32_t control;
  __asm volatile("mrs %0, control" : "=r"(control));
  return control;
}

void __set__CONTROL_PRIVILEGE_LEVEL(CONTROL_PrivilegeLevel level) {
  uint32_t control = __get_CONTROL();

  if (level == CONTROL_PRIVILEGED) {
    control &= ~CONTROL_nPRIV;
  } else {
    control |= CONTROL_nPRIV;
  }

  __set__CONTROL(control);
}

void __set__CONTROL_STACK_POINTER(CONTROL_StackPointer stack) {
  uint32_t control = __get_CONTROL();

  if (stack == CONTROL_STACK_MSP) {
    control &= ~CONTROL_SPSEL;
  } else {
    control |= CONTROL_SPSEL;
  }

  __set__CONTROL(control);
}

void __set__CONTROL_FPU(CONTROL_FloatingPoint fp) {
  uint32_t control = __get_CONTROL();

  if (fp == CONTROL_FP_DISABLED) {
    control &= ~CONTROL_FPCA;
  } else {
    control |= CONTROL_FPCA;
  }

  __set__CONTROL(control);
}

CONTROL_PrivilegeLevel __get__CONTROL_PRIVILEGE_LEVEL(void) {
  uint32_t control = __get_CONTROL();

  return (control & CONTROL_nPRIV) ? CONTROL_UNPRIVILEGED : CONTROL_PRIVILEGED;
}

CONTROL_StackPointer __get__CONTROL_STACK_POINTER(void) {
  uint32_t control = __get_CONTROL();

  return (control & CONTROL_SPSEL) ? CONTROL_STACK_PSP : CONTROL_STACK_MSP;
}

CONTROL_FloatingPoint __get__CONTROL_FPU(void) {
  uint32_t control = __get_CONTROL();

  return (control & CONTROL_FPCA) ? CONTROL_FP_ENABLED : CONTROL_FP_DISABLED;
}

uint32_t __get_MSP(void) {
  uint32_t result;
  __asm volatile("MRS %0, MSP" : "=r"(result));
  return result;
}

void __set_MSP(uint32_t topOfMainStack) {
  __asm volatile("MSR MSP, %0" : : "r"(topOfMainStack));
}

uint32_t __get_PSP(void) {
  uint32_t result;
  __asm volatile("MRS %0, PSP" : "=r"(result));
  return result;
}

void __set_PSP(uint32_t topOfProcessStack) {
  __asm volatile("MSR PSP, %0" : : "r"(topOfProcessStack));
}

#endif // CONTROL_H