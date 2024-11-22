// Startup code
#include "systick.h"
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "common.h"

static char greet[] = "Hello World!\n";
static char exit[] = "Press ctrl-A then X to exit\n";
static char monitor[] = "Press ctrl-A then C to open monitor\n";

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

int main(void)
{
  // Missing devices
  // Reset and Clock Controller (RCC) (other features than reset and enable)
  // qemu nie wspiera rcc
  // clock_init();
  // wziązku z tym systick średnio działa

  uart_init(UART1, 9600);
  usart_write(UART1, greet, length(greet));
  usart_write(UART1, monitor, length(monitor));
  usart_write(UART1, exit, length(exit));

  // echo(UART1);

  systick_init(FREQ / 1000); // Tick every 1 ms
  uint64_t current_time = systick_get_ticks();
  char x[2];
  x[0] = 'a';
  x[1] = '\n';
  while (1)
  {
    // task1
    if (systick_get_ticks() - current_time >= 1000)
    {
      usart_write(UART1, &x, 2);
      x[0]++;
      if (x[0] > 'z')
        x[0] = 'a';
      current_time = systick_get_ticks();
    }
    // delay(3000);

    // task2
    echo(UART1);

    // delay(1000);
  }
  return 0;
}
