#include "mpu.h"
#include "scb.h"
#include "uart.h"

/* If a program accesses a memory location that is prohibited by the MPU, the
processor generates a memory management fault. This causes a fault exception,
and might cause termination of the process in an OS environment. */
extern uart_handle_t uart1;

void mem_manage_handler(void) {
  uint32_t fault_address = SCB->MMAR;
  uint32_t fault_status = SCB->CFSR;

  if (fault_status & (1 << 0)) {
    usart_write(&uart1, (uint8_t *)"Instruction access violation\n", 30);
  }
  if (fault_status & (1 << 1)) {
    usart_write(&uart1, (uint8_t *)"Data access violation\n", 23);
  }
  if (fault_status & (1 << 3)) {
    usart_write(&uart1, (uint8_t *)"Precise data access violation\n", 31);
  }
  if (fault_status & (1 << 4)) {
    usart_write(&uart1, (uint8_t *)"Imprecise data access violation\n", 33);
  }
  // mmarvalid
  if (fault_status & (1 << 7)) {
    usart_write(&uart1, (uint8_t *)"MMAR valid\n", 12);
  }

  usart_write(&uart1, (uint8_t *)"Memory management fault\n", 25);

  while (1) {
  }
}

void mpu_enable() { MPU->CTRL |= MPU_CTRL_ENABLE | MPU_CTRL_PRIVDEFENA; }

void mpu_disable() { MPU->CTRL = 0; }

#define MPU_REGION_SIZE_128B (0x06 << 1)
#define MPU_REGION_SIZE_1MB (0x13 << 1)
#define MPU_REGION_FULL_ACCESS (0x03 << 24) // Full access (read/write)
#define MPU_REGION_NO_ACCESS (0x00 << 24)   // No access
#define MPU_REGION_READ_ONLY (0x01 << 24)   // Read-only
#define MPU_REGION_EXECUTE (0x01 << 28)     // Execute permission
#define MPU_REGION_NO_EXECUTE (0x00 << 28)  // No execute

static inline void __DSB(void) { __asm volatile("dsb 0xF" ::: "memory"); }

static inline void __ISB(void) { __asm volatile("isb 0xF" ::: "memory"); }

void mpu_init() {
  MPU->CTRL = 0x0; // disable MPU

  /*  MPU->RNR = 0x0; // set region 0

   MPU->RBAR = 0xE0000000; // Base Address of the region
   MPU->RASR = (0 | MPU_REGION_SIZE_128B | 0x0 << 16 | 0x0 << 17 | 0x0 << 18 |
   0x3 << 24 | 0x0 << 28);
  */
  /*   // core periphals
    MPU->RNR = 0x1;         // set region 1
    MPU->RBAR = 0xE000E000; // set base address
    MPU->RASR = (MPU_REGION_SIZE_128B) | (MPU_REGION_NO_ACCESS) |
    (MPU_REGION_NO_EXECUTE);
    // subregion 0

    // enable system control space
    MPU->RNR = 0x2;         // set region 2
    MPU->RBAR = 0xE000E000; // set base address
    MPU->RASR = (MPU_REGION_SIZE_1MB) | (MPU_REGION_FULL_ACCESS) |
    (MPU_REGION_NO_EXECUTE); */

  MPU->CTRL |= MPU_CTRL_ENABLE | MPU_CTRL_PRIVDEFENA;
  __DSB();
  __ISB();
}

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=28&zoom=100,89,117

// ustawianie regionu
//  setup memory protection unit
/*  MPU->CTRL = 0x0;        // disable MPU
 MPU->RNR = 0x0;         // set region 0
 MPU->RBAR = 0x20000000; // set base address
 MPU->RASR = BIT(0) | (0x3 << 24) | (0x7 << 1) | BIT(28); */
// MPU->CTRL = BIT(0) | BIT(1);