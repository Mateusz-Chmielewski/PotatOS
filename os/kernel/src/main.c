#include "mpu.h"
#include "rcc.h"
#include "system_calls.h"
#include "uart.h"

// os stuff
#include "os.h"
#include "osLib.h"
#include "task.h"

uart_handle_t uart1 = {UART1, 0};
uart_handle_t uart2 = {UART2, 0};
uart_handle_t uart3 = {UART3, 0};

// taski działają w trybie unprivileged
// dostęp do peryferiów tylko w trybie privileged
// mam dostęp do peryferiów za pomocą system callów
void task1(void) {

  {
    uint8_t greet[] = "Hello in kernel cli!\n";
    usart_syscall_write(&uart1, greet, length(greet));
  }
  cli(&uart1);

  while (1)
    ;
}

void task2(void) {
  char *msg = "Task 2 -- ";
  char msg2[2] = {'a', '\n'};

  while (1) {
    usart_syscall_write(&uart2, (uint8_t *)msg, length(msg));
    usart_syscall_write(&uart2, (uint8_t *)msg2, 2);

    msg2[0]++;
    if (msg2[0] > 'z') {
      msg2[0] = 'a';
    }

    syscall_delay(1000);
  }
}

void task3(void) {

  char *msg = "Task 3 -- ";
  char msg2[2] = {'0', '\n'};

  while (1) {
    usart_syscall_write(&uart3, (uint8_t *)msg, length(msg));
    usart_syscall_write(&uart3, (uint8_t *)msg2, 2);

    msg2[0]++;

    if (msg2[0] > '9') {
      msg2[0] = '0';
    }
    syscall_delay(2000);
  }
}

int main(void) {
  // peripheral stuff
  rcc_gpioa_enable();
  rcc_usart1_enable();
  rcc_usart2_enable();
  rcc_usart3_enable();

  uart_init(&uart1, 9600U);
  uart_init(&uart2, 9600U);
  uart_init(&uart3, 9600U);

  mpu_init();

  // os stuff
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
