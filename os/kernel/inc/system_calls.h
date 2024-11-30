#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "uart.h"
#include <stdint.h>

#define SYS_USART_WRITE 1
#define SYS_USART_READ 2

void usart_syscall_write(uint32_t *data, uint32_t length);
void usart_syscall_read(struct uart_handle_t *uart_handle, char *buffer,
                        uint32_t length);

void chuj(uint32_t x, uint32_t y, uint32_t z);

// define system calls
#define SYS_USART_WRITE 1
#define SYS_USART_READ 2

#endif // SYSTEM_CALLS_H