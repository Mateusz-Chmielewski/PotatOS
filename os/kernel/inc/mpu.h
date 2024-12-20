#ifndef MPU_H
#define MPU_H

#include <stdint.h>

/*
Memory Protection Unit (MPU)

The MPU divides the memory map into a number of regions, and defines the
location, size, access permissions, and memory attributes of each region.

If a program accesses a memory location that is prohibited by the MPU, the
processor generates a memory management fault. This causes a fault exception,
and might cause termination of the process in an OS environment. termination of
the process in an OS environment.

https://www.st.com/resource/en/datasheet/cd00237391.pdf#page=20

https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=193&zoom=100,165,556
 */

typedef struct Mpu {
  volatile uint32_t TYPER, CTRL, RNR, RBAR, RASR;
} Mpu;

#define MPU ((Mpu *)0xE000ED90)

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