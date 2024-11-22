// Startup code
#include "drivers/inc/systick.h"
#include "drivers/inc/uart.h"
#include "drivers/inc/rcc.h"
#include "drivers/inc/gpio.h"
#include "drivers/inc/common.h"
#include "utils.h"

static char greet[] = "Hello World!\n";
static char exit[] = "Press ctrl-A then X to exit\n";
static char monitor[] = "Press ctrl-A then C to open monitor\n";

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
