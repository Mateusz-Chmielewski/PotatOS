#include "gpio.h"
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
    uint8_t greet[] = "Hello in kernel cli!\n\r";
    usart_syscall_write(&uart3, greet, length(greet));
  }
  cli(&uart3);

  while (1)
    ;
}

void task2(void) {

  uint16_t ledGreen = PIN('B', 0);                // Green LED
  syscall_gpio_set_mode(ledGreen, GPIO_MODE_OUT); // Set blue LED to output mode

  while (1) {
    syscall_gpio_write(ledGreen, 1);
    syscall_delay(1000);
    syscall_gpio_write(ledGreen, 0);
    syscall_delay(1000);
  }
}

void task3(void) {

  uint16_t ledRed = PIN('B', 14);               // RED LED
  syscall_gpio_set_mode(ledRed, GPIO_MODE_OUT); // Set blue LED to output mode

  while (1) {
    syscall_gpio_write(ledRed, 1);
    syscall_delay(2000);
    syscall_gpio_write(ledRed, 0);
    syscall_delay(2000);
  }
}

void task6(void) {
  uint16_t ledBlue = PIN('B', 7);                // Blue LED
  syscall_gpio_set_mode(ledBlue, GPIO_MODE_OUT); // Set blue LED to output mode

  uint16_t buttonB1 = PIN('C', 13);              // Blue button
  syscall_gpio_set_mode(buttonB1, GPIO_MODE_IN); // Set button to input mode

  int toggle = 0;
  int ledState = 0;

  while (1) {
    uint8_t read = 0;

    // on button press
    syscall_gpio_read(buttonB1, &read);
    if (read == 1) {
      syscall_delay(50);
      syscall_gpio_read(buttonB1, &read);

      if (read == 1 && toggle == 0) {
        toggle = 1;

        ledState = !ledState;
        syscall_gpio_write(ledBlue, ledState);
      }
    } else {
      toggle = 0;
    }

    //on button hold
    // syscall_gpio_read(buttonB1, &read);
    //  if (read == 1) {
    //   syscall_gpio_write(ledBlue, 1);
    // } else {
    //   syscall_gpio_write(ledBlue, 0);
    // }
  }
}

void task4(void) {
  char *msg = "Task 4 -- ";
  char msg2[3] = {'a', '\n', '\r'};

  while (1) {
    usart_syscall_write(&uart3, (uint8_t *)msg, length(msg));
    usart_syscall_write(&uart3, (uint8_t *)msg2, 3);
    msg2[0]++;
    if (msg2[0] > 'z') {
      msg2[0] = 'a';
    }

    syscall_delay(5000);
  }
}

void task5(void) {
  char *msg = "Task 5 -- ";
  char msg2[3] = {'a', '\n', '\r'};

  while (1) {
    syscall_delay(10000);
    usart_syscall_write(&uart3, (uint8_t *)msg, length(msg));
    usart_syscall_write(&uart3, (uint8_t *)msg2, 3);

    msg2[0]++;
    if (msg2[0] > 'z') {
      msg2[0] = 'a';
    }
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

  //memory protection unit
  mpu_init();

  // os stuff
  osEnableProcessorFaults();
  initScheduler();

  osTaskCreate(task1);
  osTaskCreate(task2);
  osTaskCreate(task3);
  osTaskCreate(task4);
  osTaskCreate(task5);
  osTaskCreate(task6);

  startScheduler();

  // never reach here
  while (1)
    ;
  return 0;
}
