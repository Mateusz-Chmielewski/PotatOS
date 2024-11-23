// Startup code
#include "systick.h"
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "common.h"
#include "utils.h"

static uint8_t greet[] = "Hello World!\n";
static uint8_t exit[] = "Press ctrl-A then X to exit\n";
static uint8_t monitor[] = "Press ctrl-A then C to open monitor\n";
static uint8_t greet2[] = "Hello World 2!\n";

uart_handle_t uart1 = {UART1, 0};
uart_handle_t uart2 = {UART2, 0};

int main(void)
{
  // Missing devices
  // Reset and Clock Controller (RCC) (other features than reset and enable)
  // qemu nie wspiera rcc
  // clock_init();
  // wziązku z tym systick średnio działa
  rcc_gpioa_enable();
  rcc_usart1_enable();

  rcc_usart2_enable();

  uart_init(&uart1, 9600U);
  uart_init(&uart2, 9600U);

  usart_write(&uart1, greet, length(greet));
  usart_write(&uart1, monitor, length(monitor));
  usart_write(&uart1, exit, length(exit));

  usart_write(&uart2, greet2, length(greet2));

  systick_init(FREQ / 1000); // Tick every 1 ms
  uint64_t current_time = systick_get_ticks();
  uint8_t x[2];
  x[0] = 'a';
  x[1] = '\n';
  while (1)
  {
    // task1
    if (systick_get_ticks() - current_time >= 1000)
    {
      usart_write(&uart1, x, 2);
      x[0]++;
      if (x[0] > 'z')
        x[0] = 'a';
      current_time = systick_get_ticks();
    }
    // delay(3000);

    // task2
    echo(&uart1);

    echo(&uart2);
  }
  return 0;
}
