#ifndef UART_H
#define UART_H

#include "common.h"
#include "memorymap.h"
#include "ringbuffer.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct Uart {
  volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
} Uart;

typedef struct UartHandler {
  struct Uart *uart;
  RingBuffer *rb;
} UartHandler;

#define USART1_BUFFER_SIZE 128
#define USART2_BUFFER_SIZE 128
#define USART3_BUFFER_SIZE 64

#define UART1 ((Uart *)UART1_BASE)
#define UART2 ((Uart *)UART2_BASE)
#define UART3 ((Uart *)UART3_BASE)
#define USART_FLAG_TXE ((uint16_t)0x0080)
#define USART_FLAG_RXNE ((uint16_t)0x0020)

#define UART_CR1_UE BIT(13)    // UART Enable
#define UART_CR1_RE BIT(2)     // Receiver Enable
#define UART_CR1_TE BIT(3)     // Transmitter Enable
#define UART_CR1_RXNEIE BIT(5) // RXNE interrupt enable

void uart_init(UartHandler *uart_handle, unsigned long baud);
void usart1_isr(void);

void usart_write(UartHandler *uart_handle, uint8_t *data,
                 const uint32_t length);
void usart_write_byte(UartHandler *uart_handle, uint8_t data);
uint32_t usart_read(UartHandler *uart_handle, uint8_t *data,
                    const uint32_t length);
bool usart_data_available(UartHandler *uart_handle);

void usart_write2(Uart *uart, uint8_t *data, const uint32_t length);

#endif // UART_H