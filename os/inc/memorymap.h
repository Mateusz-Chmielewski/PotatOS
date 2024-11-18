
#include <stdint.h>

#ifndef __REG_H_
#define __REG_H_

#define __REG_TYPE volatile uint32_t
#define __REG __REG_TYPE *

#define GPIO_BASE 0x40020000
#define RCC_BASE 0x40023800
#define SYSTICK_BASE 0xE000E010
#define UART1_BASE 0x40011000
#define UART2_BASE 0x40004400
#define UART3_BASE 0x40004800

#endif
