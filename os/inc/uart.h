#ifndef UART_H
#define UART_H

#include <stdint.h>
#define FREQ 16000000 // CPU frequency, 16 Mhz

struct uart
{
  volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
};

#define UART1 ((struct uart *)0x40011000)
#define UART2 ((struct uart *)0x40004400)
#define UART3 ((struct uart *)0x40004800)
#define USART_FLAG_TXE ((uint16_t)0x0080)
#define USART_FLAG_RXNE ((uint16_t)0x0020)

void uart_init(struct uart *uart, unsigned long baud);
void print_str(struct uart *uart, const char *str);
uint8_t read_byte(struct uart *uart);

#endif // UART_H