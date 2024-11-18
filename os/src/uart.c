#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include <stdint.h>
#include "common.h"

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

  // clock enable
  if (uart == UART1)
    RCC->APB2ENR |= BIT(4);
  if (uart == UART2)
    RCC->APB1ENR |= BIT(17);
  if (uart == UART3)
    RCC->APB1ENR |= BIT(18);

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
}

void print_str(struct uart *uart, const char *str)
{
  while (*str)
  {
    while (!((uart->SR) & USART_FLAG_TXE)) // Wait for the transmission buffer to be empty
      ;
    uart->DR = (*str & 0xFF);
    str++;
  }
}

uint8_t read_byte(struct uart *uart)
{
  uint8_t byte;
  while (!(uart->SR & USART_FLAG_RXNE)) // RXNE ready to read
    ;
  byte = *(uint8_t *)&uart->DR;
  return byte;
}