// Startup code
#include "systick.h"
#include "main.h"
#include "uart.h"

static char greet[] = "Hello World!\n";
static char exit[] = "Press ctrl-A then X to exit\n";
static char monitor[] = "Press ctrl-A then C to open monitor\n";

void echo(struct uart *uart)
{
  char buf[2];
  while (1)
  {
    uint8_t x = read_byte(uart);
    buf[0] = x;
    buf[1] = '\0';
    if (x == 13)
    {
      print_str(uart, "\n");
    }
    else
    {
      print_str(uart, buf);
    }
  }
}

int main(void)
{
  uart_init(UART1, 9600);
  print_str(UART1, exit);
  print_str(UART1, monitor);
  print_str(UART1, greet);

  // echo(UART1);
  systick_init(16000000 / 1000); // Tick every 1 ms
  uint64_t current_time = systick_get_ticks();

  while (1)
  {
    if (systick_get_ticks() - current_time >= 10000)
    {
      print_str(UART1, "Hello World!\n");
      current_time = systick_get_ticks();
    }
  }
  return 0;
}
