#include "gpio.h"
#include "mpu.h"
#include "rcc.h"
#include "system_calls.h"
#include "systick.h"
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

  /*  {
     uint8_t greet[] = "Hello in kernel cli!\n";
     usart_syscall_write(&uart1, greet, length(greet));
   }
   cli(&uart1);

   while (1)
     ; */

  uint16_t ledRed = PIN('B', 14);       // Blue LED
  RCC->AHB1ENR |= BIT(PINBANK(ledRed)); // Enable GPIO clock for LED
  gpio_set_mode(ledRed, GPIO_MODE_OUT); // Set blue LED to output mode

  while (1) {
    gpio_write(ledRed, 1);
    syscall_delay(3000);
    gpio_write(ledRed, 0);
    syscall_delay(3000);
  }
}

void task2(void) {
  // char *msg = "Task 2 -- ";
  // char msg2[3] = {'a', '\n', '\r'};
  //  usart_syscall_write(&uart3, (uint8_t *)msg, length(msg));

  uint16_t ledRed = PIN('B', 0);        // Green LED
  RCC->AHB1ENR |= BIT(PINBANK(ledRed)); // Enable GPIO clock for LED
  gpio_set_mode(ledRed, GPIO_MODE_OUT); // Set blue LED to output mode

  while (1) {
    gpio_write(ledRed, 1);
    syscall_delay(2000);
    gpio_write(ledRed, 0);
    syscall_delay(2000);

    /* msg2[0]++;
    if (msg2[0] > 'z') {
      msg2[0] = 'a';
    } */
  }
}

void task3(void) {

  char *msg = "Task 3 -- ";
  char msg2[3] = {'a', '\n', '\r'};

  while (1) {
    usart_syscall_write(&uart3, (uint8_t *)msg, length(msg));
    usart_syscall_write(&uart3, (uint8_t *)msg2, 3);

    msg2[0]++;

    if (msg2[0] > '9') {
      msg2[0] = '0';
    }
    // syscall_delay(2000);

    task_delay(2000);
  }
}

// t: expiration time, prd: period, now: current time. Return true if expired
bool timer_expired(uint32_t *t, uint32_t prd, uint32_t now) {
  if (now + prd < *t)
    *t = 0; // Time wrapped? Reset timer
  if (*t == 0)
    *t = now + prd; // First poll? Set expiration
  if (*t > now)
    return false;                               // Not expired yet, return
  *t = (now - *t) > prd ? now + prd : *t + prd; // Next expiration time
  return true;                                  // Expired, return true
}

int main(void) {

  // works
  // uint16_t ledRed = PIN('B', 14);       // Blue LED
  // RCC->AHB1ENR |= BIT(PINBANK(ledRed)); // Enable GPIO clock for LED
  // gpio_set_mode(ledRed, GPIO_MODE_OUT); // Set blue LED to output mode
  // gpio_write(ledRed, 1);

  // uint16_t ledBlue = PIN('B', 7);
  // RCC->AHB1ENR |= BIT(PINBANK(ledBlue));
  // gpio_set_mode(ledBlue, GPIO_MODE_OUT);
  // gpio_write(ledBlue, 1);

  // uint16_t ledGreen = PIN('B', 0);
  // RCC->AHB1ENR |= BIT(PINBANK(ledGreen));
  // gpio_set_mode(ledGreen, GPIO_MODE_OUT);
  // gpio_write(ledGreen, 1);

  // peripheral stuff
  rcc_gpioa_enable();
  rcc_usart1_enable();
  rcc_usart2_enable();
  rcc_usart3_enable();

  uart_init(&uart1, 9600U);
  uart_init(&uart2, 9600U);
  uart_init(&uart3, 9600U);

  // to cos wywala chyba mapowanie pamięci inne data access violation
  // mpu_init();

  // os stuff
  osEnableProcessorFaults();
  initScheduler();

  osTaskCreate(task1);
  osTaskCreate(task2);
  //   osTaskCreate(task3);

  startScheduler();

  /* systick_init(FREQ / 1000); // Tick every 1 ms

  uint32_t timer, period = 500;    // Declare timer and 500ms period
  uint32_t timer2, period2 = 1000; // Declare timer and 500ms period

  for (;;) {
    if (timer_expired(&timer, period, systick_get_ticks())) {
      static bool on;         // This block is executed
      gpio_write(ledRed, on); // Every `period` milliseconds
      on = !on;               // Toggle LED state
    }

    if (timer_expired(&timer2, period2, systick_get_ticks())) {
      static bool on;          // This block is executed
      gpio_write(ledBlue, on); // Every `period` milliseconds
      on = !on;                // Toggle LED state
    }
    // Here we could perform other activities!
  } */

  // never reach here
  while (1)
    ;
  return 0;
}
