#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "memory.h"
#include <stdbool.h>
#include "common.h"
#include "ringbuffer.h"

struct uart
{
  volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
};

typedef struct uart_handle_t
{
  struct uart *uart;
  ringbuffer_t *rb;
} uart_handle_t;

#define USART1_BUFFER_SIZE 128
#define USART2_BUFFER_SIZE 128
#define USART3_BUFFER_SIZE 64

#define UART1 ((struct uart *)UART1_BASE)
#define UART2 ((struct uart *)UART2_BASE)
#define UART3 ((struct uart *)UART3_BASE)
#define USART_FLAG_TXE ((uint16_t)0x0080)
#define USART_FLAG_RXNE ((uint16_t)0x0020)

#define UART_CR1_UE BIT(13)    // UART Enable
#define UART_CR1_RE BIT(2)     // Receiver Enable
#define UART_CR1_TE BIT(3)     // Transmitter Enable
#define UART_CR1_RXNEIE BIT(5) // RXNE interrupt enable

void uart_init(struct uart_handle_t *uart_handle, unsigned long baud);
void usart1_isr(void);

void usart_write(struct uart_handle_t *uart_handle, uint8_t *data, const uint32_t length);
void usart_write_byte(struct uart_handle_t *uart_handle, uint8_t data);
uint32_t usart_read(struct uart_handle_t *uart_handle, uint8_t *data, const uint32_t length);
bool usart_data_available(struct uart_handle_t *uart_handle);

#endif // UART_H