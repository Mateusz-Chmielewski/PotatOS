#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

void usart_syscall_write(UartHandler *usart, uint32_t *data, uint32_t length);
void usart_syscall_read(UartHandler *usart, char *buffer, uint32_t length);

void syscall_delay(uint32_t ms);
void syscall_gpio_set_mode(uint16_t pin, uint8_t mode);
void syscall_gpio_write(uint16_t pin, bool val);
void syscall_gpio_read(uint16_t pin, uint8_t *val);

// define system calls
#define SYS_USART_WRITE 1
#define SYS_USART_READ 2
#define SYS_DELAY 10
#define SYS_GPIO_SET_MODE 11
#define SYS_GPIO_WRITE 12
#define SYS_GPIO_READ 13

#endif // SYSTEM_CALLS_H