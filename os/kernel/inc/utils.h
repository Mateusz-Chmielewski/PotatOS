#include <stdint.h>
#include <stdbool.h>
#include "drivers/inc/uart.h"

void echo(struct uart *uart)
{
  while (usart_data_available(UART1))
  {
    char buf[2];
    uint8_t x;
    (void)usart_read(UART1, &x, 1);
    buf[0] = x;
    buf[1] = '\0';
    if (x == 13)
    {
      usart_write(UART1, "\n", 1);
    }
    else
    {
      usart_write(UART1, buf, 1);
    }
  }
}

uint32_t length(const char *str)
{
  uint32_t len = 0;
  while (*str)
  {
    len++;
    str++;
  }
  return len;
}

void clock_init(void)
{
  // 8hz HSI
  /*  // Wlaczenie HSI, wpisanie wartosci 1
   RCC->CR |= BIT(0);

   while (!(RCC->CR & BIT(1)))
     ;

   // clear 2 first bytes
   // set HSI as clock source
   RCC->CFGR = (uint32_t)0x00000000;
   RCC->PLLCFGR = (uint32_t)0x24003010;
   RCC->CIR = 0x00000000; */
}