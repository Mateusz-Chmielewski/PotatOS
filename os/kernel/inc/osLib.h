#ifndef OS_LIB_H
#define OS_LIB_H

#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

void echo(struct uart_handle_t *uart) {
  while (usart_data_available(uart)) {
    uint8_t buf[2];
    uint8_t x;
    (void)usart_read(uart, &x, 1);
    buf[0] = x;
    buf[1] = '\0';
    if (x == 13) {
      usart_write(uart, (uint8_t *)"\n", 1);
    } else {
      usart_write(uart, buf, 1);
    }
  }
}

uint32_t length(const uint8_t *str) {
  uint32_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}

#endif // OS_LIB_H