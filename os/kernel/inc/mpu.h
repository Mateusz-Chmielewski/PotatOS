#ifndef MPU_H
#define MPU_H

#include <stdint.h>

// https://www.st.com/resource/en/datasheet/cd00237391.pdf#page=20
// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=193&zoom=100,165,556
struct mpu {
  volatile uint32_t TYPER, CTRL, RNR, RBAR, RASR;
};

#define MPU ((struct mpu *)0xE000ED90)

#define MPU_CTRL_ENABLE BIT(0) // enable MPU

/* PRIVDEFENA controls whether or not code running in Privileged thread mode can
access the default memory map. If the bit is set to 0, any access not explicitly
enabled via the MPU will result in a fault when the ENABLE bit is set. In a
typical configuration using the MPU, this bit will be set to 1. */
#define MPU_CTRL_HFNMIENA                                                      \
  BIT(1) // enable MPU during hard fault, NMI, and fault masked interrupt

#define MPU_CTRL_PRIVDEFENA                                                    \
  BIT(2) // enable privileged access to default memory map

void mpu_enable();
void mpu_disable();
void mpu_init();

#endif // MPU_H