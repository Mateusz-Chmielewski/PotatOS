#include "common.h"
#include "osLib.h"
#include "rcc.h"
#include "systick.h"
#include "uart.h"

// os stuff
#include "os.h"
#include "task.h"

uart_handle_t uart1 = {UART1, 0};
uart_handle_t uart2 = {UART2, 0};
uart_handle_t uart3 = {UART3, 0};

void task1(void) {

  uint8_t greet[] = "Hello in kernel!\n";
  usart_write(&uart2, greet, length(greet));

  while (1) {
    echo(&uart2);
  };
}

void task2(void) {
  char *msg = "Task 2 -- ";
  char msg2[2] = {'a', '\n'};

  while (1) {
    usart_write(&uart1, (uint8_t *)msg, length(msg));
    usart_write(&uart1, (uint8_t *)msg2, 2);

    msg2[0]++;
    if (msg2[0] > 'z') {
      msg2[0] = 'a';
    }
    task_delay(1000);
  }
}

void task3(void) {

  char *msg = "Task 3 -- ";
  char msg2[2] = {'0', '\n'};

  while (1) {
    usart_write(&uart3, (uint8_t *)msg, length(msg));
    usart_write(&uart3, (uint8_t *)msg2, 2);

    msg2[0]++;

    if (msg2[0] > '9') {
      msg2[0] = '0';
    }
    task_delay(2000);
  }
}

int main(void) {
  // using MSP stack
  rcc_gpioa_enable();
  rcc_usart1_enable();
  rcc_usart2_enable();
  rcc_usart3_enable();

  uart_init(&uart1, 9600U);
  uart_init(&uart2, 9600U);
  uart_init(&uart3, 9600U);

  osEnableProcessorFaults();
  initScheduler();

  osTaskCreate(task1);
  osTaskCreate(task2);
  osTaskCreate(task3);

  startScheduler();

  // never reach here
  while (1)
    ;
  return 0;
}
