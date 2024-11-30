#include "uart.h"
#include "common.h"
#include "gpio.h"
#include "ringbuffer.h"
#include <stdint.h>

static ringbuffer_t usart1_rb = {0};
static ringbuffer_t usart2_rb = {0};
static ringbuffer_t usart3_rb = {0};
static uint8_t usart1_rb_buffer[USART1_BUFFER_SIZE] = {0};
static uint8_t usart2_rb_buffer[USART2_BUFFER_SIZE] = {0};
static uint8_t usart3_rb_buffer[USART3_BUFFER_SIZE] = {0};

void uart_init(struct uart_handle_t *uart_handle, unsigned long baud) {
  /* USART bidirectional communication requires a minimum of two pins: Receive
  Data In (RX) and Transmit Data Out (TX): */
  // https://controllerstech.com/how-to-setup-uart-using-registers-in-stm32/
  // 1. Enable the USARTX peripheral clock
  // 2. Configure the GPIO pins for USART2 Tx and Rx (PA2 and PA3) in alternate
  // function mode
  // https://www.st.com/resource/en/datasheet/stm32f405zg.pdf#page=63
  // 3. select which alternate function to use for the pins (AF7 for USART2)
  // https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=275

  uint8_t af = 7;          // Alternate function
  uint16_t rx = 0, tx = 0; // pins

  // pin configuration
  if (uart_handle->uart == UART1)
    tx = PIN('A', 9), rx = PIN('A', 10);
  if (uart_handle->uart == UART2)
    tx = PIN('A', 2), rx = PIN('A', 3);
  if (uart_handle->uart == UART3)
    tx = PIN('D', 8), rx = PIN('D', 9);

  gpio_set_mode(tx, GPIO_MODE_AF);
  gpio_set_af(tx, af);
  gpio_set_mode(rx, GPIO_MODE_AF);
  gpio_set_af(rx, af);

  if (uart_handle->uart == UART1) {
    ringbuffer_init(&usart1_rb, usart1_rb_buffer, USART1_BUFFER_SIZE);
    uart_handle->rb = &usart1_rb;
  }
  if (uart_handle->uart == UART2) {
    ringbuffer_init(&usart2_rb, usart2_rb_buffer, USART2_BUFFER_SIZE);
    uart_handle->rb = &usart2_rb;
  }
  if (uart_handle->uart == UART3) {
    ringbuffer_init(&usart3_rb, usart3_rb_buffer, USART3_BUFFER_SIZE);
    uart_handle->rb = &usart3_rb;
  }

  uart_handle->uart->CR1 = 0;
  uart_handle->uart->BRR = FREQ / baud; // FREQ is a UART bus frequency
  uart_handle->uart->CR1 |= UART_CR1_UE | UART_CR1_RE |
                            UART_CR1_TE; // Set UE (uart enable), RE (read
                                         // enable), TE(transmision enable) bits
  uart_handle->uart->CR1 |=
      UART_CR1_RXNEIE; // Enable RXNE interrupt (interrupt on read)

  // nvic enable usart1
  // page 210
  // https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf

  // Enable interrupt from NVIC (TODO write api for nvic?)
  if (uart_handle->uart == UART1)
    NVIC_ISER1 |= BIT(5); // Enable interrupt for USART1
  if (uart_handle->uart == UART2)
    NVIC_ISER1 |= BIT(6); // Enable interrupt for USART2
  if (uart_handle->uart == UART3)
    NVIC_ISER1 |= BIT(7); // Enable interrupt for USART3
}

void usart1_isr(void) {
  // interrupt saves the data to the buffer
  const bool received_data = UART1->SR & USART_FLAG_RXNE;

  if (received_data) {
    ringbuffer_write(&usart1_rb, UART1->DR);
  }
}

void usart2_isr(void) {
  const bool received_data = UART2->SR & USART_FLAG_RXNE;

  if (received_data) {
    ringbuffer_write(&usart2_rb, UART2->DR);
  }
}

void usart3_isr(void) {
  const bool received_data = UART3->SR & USART_FLAG_RXNE;

  if (received_data) {
    ringbuffer_write(&usart3_rb, UART3->DR);
  }
}

void usart_write(struct uart_handle_t *uart_handle, uint8_t *data,
                 const uint32_t length) {
  for (uint32_t i = 0; i < length; i++) {
    usart_write_byte(uart_handle, data[i]);
  }
}

void usart_write_byte(struct uart_handle_t *uart_handle, uint8_t data) {
  while (!(uart_handle->uart->SR & USART_FLAG_TXE))
    ;
  uart_handle->uart->DR = data;
}

uint32_t usart_read(struct uart_handle_t *uart_handle, uint8_t *data,
                    const uint32_t length) {
  if (length == 0) {
    return 0;
  }

  for (uint32_t bytes_read = 0; bytes_read < length; bytes_read++) {
    if (!ringbuffer_read(uart_handle->rb, &data[bytes_read])) {
      return bytes_read;
    }
  }

  return length;
}

bool usart_data_available(struct uart_handle_t *uart_handle) {
  return !ringbuffer_empty(uart_handle->rb);
}