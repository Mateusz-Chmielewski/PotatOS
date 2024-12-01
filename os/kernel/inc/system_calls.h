#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

void usart_syscall_write(uart_handle_t *usart, uint32_t *data, uint32_t length);
void usart_syscall_read(uart_handle_t *usart, char *buffer, uint32_t length);

void syscall_delay(uint32_t ms);

// define system calls
#define SYS_USART_WRITE 1
#define SYS_USART_READ 2
#define SYS_DELAY 10

#endif // SYSTEM_CALLS_H