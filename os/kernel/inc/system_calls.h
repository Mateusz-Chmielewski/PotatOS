#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "uart.h"
#include <stdint.h>

// void usart_syscall_write(uint32_t *data, uint32_t length);

void usart1_syscall_write(uint32_t *data, uint32_t length);
void usart2_syscall_write(uint32_t *data, uint32_t length);
void usart3_syscall_write(uint32_t *data, uint32_t length);

void usart1_syscall_read(char *buffer, uint32_t length);

void chuj(uint32_t x, uint32_t y, uint32_t z);

// define system calls
#define SYS_USART1_WRITE 1
#define SYS_USART2_WRITE 1
#define SYS_USART3_WRITE 1
#define SYS_USART1_READ 2

#endif // SYSTEM_CALLS_H