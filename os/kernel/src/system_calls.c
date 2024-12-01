#include "system_calls.h"
#include "uart.h"

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

  uint32_t x = stack_frame[0];
  uint32_t y = stack_frame[1];
  uint32_t z = stack_frame[2];

  uint32_t return_address = stack_frame[6]; // PC where SVC was executed
  uint16_t svc_instruction =
      *((uint16_t *)(return_address - 2));     // Fetch SVC instruction
  uint8_t svc_number = svc_instruction & 0xFF; // Extract SVC number

  switch (svc_number) {
  case SYS_USART1_WRITE:
    extern uart_handle_t uart1;
    usart_write(&uart1, (uint8_t *)stack_frame[0], (uint32_t)stack_frame[1]);
    break;
  case SYS_USART1_READ:
    extern uart_handle_t uart1;
    usart_read(&uart1, (uint8_t *)stack_frame[0], (uint32_t)stack_frame[1]);
    break;
  default:
    break;
  }
  return;
}

#define asdf 234

void chuj(uint32_t x, uint32_t y, uint32_t z) {
  __asm volatile("mov r0, %0 \n"
                 "mov r1, %1 \n"
                 "mov r2, %2 \n"
                 "svc 3 \n"
                 :
                 : "r"(x), "r"(y), "r"(z));
}

void usart1_syscall_write(uint32_t *data, uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART1_WRITE));
}

void usart2_syscall_write(uint32_t *data, uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART2_WRITE));
}

void usart3_syscall_write(uint32_t *data, uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART3_WRITE));
}

void usart1_syscall_read(char *buffer, uint32_t length) {
  __asm volatile("svc %0 \n" : : "i"(SYS_USART1_READ));
}
