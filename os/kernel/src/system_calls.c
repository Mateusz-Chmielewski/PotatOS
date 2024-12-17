#include "system_calls.h"
#include "task.h"
#include "uart.h"
#include "gpio.h"

__attribute((naked)) void sv_call_handler(void) {
  __asm volatile(
      "TST lr, #4                 \n"    // Check EXC_RETURN (Thumb state)
      "ITE EQ                     \n"    // If-Then-Else block
      "MRSEQ r0, MSP              \n"    // If equal, Main Stack Pointer (MSP)
      "MRSNE r0, PSP              \n"    // If not equal, Process Stack Pointer
                                         // (PSP)
      "B svc_handler_main            \n" // Branch to C function
  );
}

static void svc_handler_main(uint32_t *stack_frame) // it is in r0
{
  // The stack frame contains register values at the time of SVC:
  // [0]: R0, [1]: R1, [2]: R2, [3]: R3
  // [4]: R12, [5]: LR, [6]: PC (return address), [7]: xPSR
  // First argument (r0) is svc_args[0]
  uint32_t return_address = stack_frame[6]; // PC where SVC was executed
  uint16_t svc_instruction =
      *((uint16_t *)(return_address - 2));     // Fetch SVC instruction
  uint8_t svc_number = svc_instruction & 0xFF; // Extract SVC number

  switch (svc_number) {
  case SYS_USART_WRITE:
    usart_write((uart_handle_t *)stack_frame[0], (uint8_t *)stack_frame[1],
                (uint32_t)stack_frame[2]);
    break;
  case SYS_USART_READ:
    usart_read((uart_handle_t *)stack_frame[0], (uint8_t *)stack_frame[1],
               (uint32_t)stack_frame[2]);
    break;
  case SYS_DELAY:
    task_delay(stack_frame[0]);
    break;
  case SYS_GPIO_SET_MODE:
    gpio_set_mode(stack_frame[0], stack_frame[1]);
    break;
  case SYS_GPIO_WRITE:
    gpio_write(stack_frame[0], stack_frame[1]);
    break;
  case SYS_GPIO_READ: 
    uint8_t r = gpio_read(stack_frame[0]);
    uint8_t *val = (uint8_t *)stack_frame[1];
    *val = r;
    break;

  default:
    break;
  }
  return;
}

void usart_syscall_write(uart_handle_t *usart, uint32_t *data,
                         uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART_WRITE));
}

void usart_syscall_read(uart_handle_t *usart, char *buffer, uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART_READ));
}

void syscall_delay(uint32_t ms) {
  __asm volatile("svc %0 \n" : : "i"(SYS_DELAY));
}

void syscall_gpio_set_mode(uint16_t pin, uint8_t mode){
  __asm volatile("svc %0 \n" : : "i"(SYS_GPIO_SET_MODE));
};

void syscall_gpio_write(uint16_t pin, bool val){
  __asm volatile("svc %0 \n" : : "i"(SYS_GPIO_WRITE));
};

void syscall_gpio_read(uint16_t pin, uint8_t *val){
  __asm volatile("svc %0 \n" : : "i"(SYS_GPIO_READ));
};