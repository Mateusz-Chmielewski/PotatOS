#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include <stdint.h>
#include "common.h"
#include "ringbuffer.h"

#define BUFFER_SIZE 128
static ringbuffer_t rb = {0};
static uint8_t buffer[BUFFER_SIZE] = {0};

void uart_init(struct uart *uart, unsigned long baud)
{
  /* USART bidirectional communication requires a minimum of two pins: Receive Data In (RX)
  and Transmit Data Out (TX): */
  // https://controllerstech.com/how-to-setup-uart-using-registers-in-stm32/
  // 1. Enable the USARTX peripheral clock
  // 2. Configure the GPIO pins for USART2 Tx and Rx (PA2 and PA3) in alternate function mode
  // https://www.st.com/resource/en/datasheet/stm32f405zg.pdf#page=63
  // 3. select which alternate function to use for the pins (AF7 for USART2)
  // https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=275

  uint8_t af = 7;          // Alternate function
  uint16_t rx = 0, tx = 0; // pins

  ringbuffer_init(&rb, buffer, BUFFER_SIZE);

  // clock enable
  if (uart == UART1)
    RCC->APB2ENR |= BIT(4); // Enable clock for USART1
  if (uart == UART2)
    RCC->APB1ENR |= BIT(17); // Enable clock for USART2
  if (uart == UART3)
    RCC->APB1ENR |= BIT(18); // Enable clock for USART3

  // pin configuration
  if (uart == UART1)
    tx = PIN('A', 9), rx = PIN('A', 10);
  if (uart == UART2)
    tx = PIN('A', 2), rx = PIN('A', 3);
  if (uart == UART3)
    tx = PIN('D', 8), rx = PIN('D', 9);

  gpio_set_mode(tx, GPIO_MODE_AF); // Set pin mode to alternate function
  gpio_set_af(tx, af);             // Set alternate function
  gpio_set_mode(rx, GPIO_MODE_AF);
  gpio_set_af(rx, af);
  uart->CR1 = 0;                          // Disable this UART
  uart->BRR = FREQ / baud;                // FREQ is a UART bus frequency
  uart->CR1 |= BIT(13) | BIT(2) | BIT(3); // Set UE (uart enable), RE (read enable), TE(transmision enable) bits
  uart->CR1 |= BIT(5);                    // Enable RXNE interrupt (interrupt on read)

  // nvic enable usart1
  // page 210
  // https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf

  // Enable interrupt from NVIC (TODO write api for nvic?)
  if (uart == UART1)
    NVIC_ISER1 |= BIT(5); // Enable interrupt for USART1
}

void usart1_isr(void)
{
  // interrupt saves the data to the buffer
  const bool received_data = UART1->SR & USART_FLAG_RXNE;

  if (received_data)
  {
    ringbuffer_write(&rb, UART1->DR);
  }
}

void usart_write(struct uart *uart, uint8_t *data, const uint32_t length)
{
  for (uint32_t i = 0; i < length; i++)
  {
    usart_write_byte(uart, data[i]);
  }
}

void usart_write_byte(struct uart *uart, uint8_t data)
{
  while (!(uart->SR & USART_FLAG_TXE))
    ;
  uart->DR = data;
}

uint32_t usart_read(struct uart *uart, uint8_t *data, const uint32_t length)
{
  if (length == 0)
  {
    return 0;
  }

  for (uint32_t bytes_read = 0; bytes_read < length; bytes_read++)
  {
    if (!ringbuffer_read(&rb, &data[bytes_read]))
    {
      return bytes_read;
    }
  }

  return length;
}

bool usart_data_available(struct uart *uart)
{
  return !ringbuffer_empty(&rb);
}