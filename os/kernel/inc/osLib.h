#ifndef OS_LIB_H
#define OS_LIB_H

#include "system_calls.h"
#include "task.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>

void echo(uart_handle_t *uart) {
  while (usart_data_available(uart)) {
    uint8_t buf[2];
    uint8_t x;
    (void)usart_syscall_read(uart, &x, 1);
    buf[0] = x;
    buf[1] = '\0';
    if (x == 13) {
      usart_syscall_write(uart, (uint8_t *)"\n", 1);
    } else {
      usart_syscall_write(uart, buf, 1);
    }
  }
}

int str_cmp(const uint8_t *str1, const uint8_t *str2) {

  const uint8_t *str1_start = str1;
  const uint8_t *str2_start = str2;

  while (*str1_start && *str2_start) {
    if (*str1_start != *str2_start) {
      return 0;
    }
    str1_start++;
    str2_start++;
  }
  return *str1_start == *str2_start;
}

uint32_t length(const uint8_t *str) {
  uint32_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (i = 0, j = length(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0) /* record sign */
    n = -n;           /* make n positive */
  i = 0;
  do {                     /* generate digits in reverse order */
    s[i++] = n % 10 + '0'; /* get next digit */
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void cli(uart_handle_t *uart) {
  uint8_t buf[40];
  int pos = 0;
  while (1) {
    while (usart_data_available(uart)) {
      uint8_t x;
      (void)usart_syscall_read(uart, &x, 1);
      buf[pos] = x;
      buf[pos + 1] = '\0';

      uint8_t buf2[2];
      buf2[0] = x;
      buf2[1] = '\0';

      if (x == 13) {
        usart_syscall_write(uart, (uint8_t *)"\n", 1);
        pos = 0;
      } else {
        usart_syscall_write(uart, buf2, 1);
        pos++;
      }

      if (str_cmp(buf, "hello\r")) {
        uint8_t msg[] = "kernel odpowiada siema!\n";
        usart_syscall_write(uart, msg, length(msg));
      }
      if (str_cmp(buf, "tasks\r")) {
        uint8_t msg[] = "running tasks count: ";
        usart_syscall_write(uart, msg, length(msg));

        uint32_t tasks_count = getTasksCount();
        char tasks_count_str[10];
        itoa(tasks_count, tasks_count_str);

        usart_syscall_write(uart, (uint8_t *)tasks_count_str,
                            length(tasks_count_str));
      }
    }
  }
}

#endif // OS_LIB_H