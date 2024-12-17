#include "mpu.h"
#include "osDefs.h"
#include "scb.h"
#include "uart.h"

// memory size
#define MPU_REGION_SIZE_4GB ((32 - 1) << MPU_RASR_SIZE_Pos) // Region size 4GB
#define MPU_REGION_SIZE_2GB ((31 - 1) << MPU_RASR_SIZE_Pos) // Region size 2GB
#define MPU_REGION_SIZE_1GB ((30 - 1) << MPU_RASR_SIZE_Pos) // Region size 1GB
#define MPU_REGION_SIZE_512MB                                                  \
  ((29 - 1) << MPU_RASR_SIZE_Pos) // Region size 512MB
#define MPU_REGION_SIZE_256MB                                                  \
  ((28 - 1) << MPU_RASR_SIZE_Pos) // Region size 256MB
#define MPU_REGION_SIZE_128MB                                                  \
  ((27 - 1) << MPU_RASR_SIZE_Pos) // Region size 128MB
#define MPU_REGION_SIZE_64MB ((26 - 1) << MPU_RASR_SIZE_Pos) // Region size 64MB
#define MPU_REGION_SIZE_32MB ((25 - 1) << MPU_RASR_SIZE_Pos) // Region size 32MB
#define MPU_REGION_SIZE_16MB ((24 - 1) << MPU_RASR_SIZE_Pos) // Region size 16MB
#define MPU_REGION_SIZE_8MB ((23 - 1) << MPU_RASR_SIZE_Pos)  // Region size 8MB
#define MPU_REGION_SIZE_4MB ((22 - 1) << MPU_RASR_SIZE_Pos)  // Region size 4MB
#define MPU_REGION_SIZE_2MB ((21 - 1) << MPU_RASR_SIZE_Pos)  // Region size 2MB
#define MPU_REGION_SIZE_1MB ((20 - 1) << MPU_RASR_SIZE_Pos)  // Region size 1MB
#define MPU_REGION_SIZE_512KB                                                  \
  ((19 - 1) << MPU_RASR_SIZE_Pos) // Region size 512KB
#define MPU_REGION_SIZE_256KB                                                  \
  ((18 - 1) << MPU_RASR_SIZE_Pos) // Region size 256KB
#define MPU_REGION_SIZE_128KB                                                  \
  ((17 - 1) << MPU_RASR_SIZE_Pos) // Region size 128KB
#define MPU_REGION_SIZE_64KB ((16 - 1) << MPU_RASR_SIZE_Pos) // Region size 64KB
#define MPU_REGION_SIZE_32KB ((15 - 1) << MPU_RASR_SIZE_Pos) // Region size 32KB
#define MPU_REGION_SIZE_16KB ((14 - 1) << MPU_RASR_SIZE_Pos) // Region size 16KB
#define MPU_REGION_SIZE_8KB ((13 - 1) << MPU_RASR_SIZE_Pos)  // Region size 8KB
#define MPU_REGION_SIZE_4KB ((12 - 1) << MPU_RASR_SIZE_Pos)  // Region size 4KB
#define MPU_REGION_SIZE_2KB ((11 - 1) << MPU_RASR_SIZE_Pos)  // Region size 2KB
#define MPU_REGION_SIZE_1KB ((10 - 1) << MPU_RASR_SIZE_Pos)  // Region size 1KB
#define MPU_REGION_SIZE_512B ((9 - 1) << MPU_RASR_SIZE_Pos)  // Region size 512B
#define MPU_REGION_SIZE_256B ((8 - 1) << MPU_RASR_SIZE_Pos)  // Region size 256B
#define MPU_REGION_SIZE_128B ((7 - 1) << MPU_RASR_SIZE_Pos)  // Region size 128B
#define MPU_REGION_SIZE_64B ((6 - 1) << MPU_RASR_SIZE_Pos)   // Region size 64B
#define MPU_REGION_SIZE_32B ((5 - 1) << MPU_RASR_SIZE_Pos)   // Region size 32B
#define MPU_REGION_SIZE_16B ((4 - 1) << MPU_RASR_SIZE_Pos)   // Region size 16B
#define MPU_REGION_SIZE_8B ((3 - 1) << MPU_RASR_SIZE_Pos)    // Region size 8B
#define MPU_REGION_SIZE_4B ((2 - 1) << MPU_RASR_SIZE_Pos)    // Region size 4B
#define MPU_REGION_SIZE_2B ((1 - 1) << MPU_RASR_SIZE_Pos)    // Region size 2B
#define MPU_REGION_SIZE_1B ((0 - 1) << MPU_RASR_SIZE_Pos)    // Region size 1B

// access permissions
#define MPU_REGION_FULL_ACCESS (0x03 << 24) // Full access (read/write)
#define MPU_REGION_NO_ACCESS (0x00 << 24)   // No access
#define MPU_REGION_READ_ONLY (0x01 << 24)   // Read-only
#define MPU_REGION_EXECUTE (0x01 << 28)     // Execute permission
#define MPU_REGION_NO_EXECUTE (0x00 << 28)  // No execute

// regions
#define FLASH_ORIGIN 0x08000000U
#define SRAM_ORIGIN 0x20000000U
#define PERIPHERAL_ORIGIN 0x40000000U

// MPU registers
#define MPU_CTRL_PRIVDEFENA_Pos (2U) // Privileged default memory map enable
#define MPU_CTRL_PRIVDEFENA_Msk (0x1UL << MPU_CTRL_PRIVDEFENA_Pos)
#define MPU_CTRL_ENABLE_Pos (0U) // Enable MPU
#define MPU_CTRL_ENABLE_Msk (0x1UL << MPU_CTRL_ENABLE_Pos)
#define MPU_RBAR_ADDR_Pos (5U)           // Base address of the region
#define MPU_RBAR_ADDR_Msk (0xFFFFFFE0UL) // Mask for the base address
#define MPU_RBAR_REGION_Pos (0U)         // Region number
#define MPU_RBAR_REGION_Msk (0x1FUL)     // Region number mask
#define MPU_RASR_XN_Pos (28U)            // Execute never bit
#define MPU_RASR_XN_Msk (0x1UL << MPU_RASR_XN_Pos)
#define MPU_RASR_AP_Pos (24U) // Access permission
#define MPU_RASR_AP_Msk (0x7UL << MPU_RASR_AP_Pos)
#define MPU_RASR_TEX_Pos (19U) // Type extension (used for cache control)
#define MPU_RASR_TEX_Msk (0x7UL << MPU_RASR_TEX_Pos)
#define MPU_RASR_SIZE_Pos (1U) // Region size
#define MPU_RASR_SIZE_Msk (0x3FUL << MPU_RASR_SIZE_Pos)
#define MPU_RASR_ENABLE_Pos (0U) // Enable region
#define MPU_RASR_ENABLE_Msk (0x1UL << MPU_RASR_ENABLE_Pos)

/* If a program accesses a memory location that is prohibited by the MPU, the
processor generates a memory management fault. This causes a fault exception,
and might cause termination of the process in an OS environment. */

void mem_manage_handler(void) {
  uint32_t fault_address = SCB->MMAR;
  uint32_t fault_status = SCB->CFSR;

  if (fault_status & (1 << 0)) {
    usart_write2(ERROR_HANDLING_UART,
                 (uint8_t *)"Instruction access violation\n", 30);
  }
  if (fault_status & (1 << 1)) {
    usart_write2(ERROR_HANDLING_UART, (uint8_t *)"Data access violation\n", 23);
  }
  if (fault_status & (1 << 3)) {
    usart_write2(ERROR_HANDLING_UART,
                 (uint8_t *)"Precise data access violation\n", 31);
  }
  if (fault_status & (1 << 4)) {
    usart_write2(ERROR_HANDLING_UART,
                 (uint8_t *)"Imprecise data access violation\n", 33);
  }
  // mmarvalid
  if (fault_status & (1 << 7)) {
    usart_write2(ERROR_HANDLING_UART, (uint8_t *)"MMAR valid\n", 12);
  }

  while (1) {
  }
}

void mpu_enable() { MPU->CTRL |= MPU_CTRL_ENABLE | MPU_CTRL_PRIVDEFENA; }

void mpu_disable() { MPU->CTRL = 0; }

void mpu_init() {
  // Disable MPU for configuration
  MPU->CTRL = 0;

  // Region 0: Flash Memory (Code/RO)
  MPU->RNR = 0;                           // Select Region 0
  MPU->RBAR = FLASH_ORIGIN;               // Base Address
  MPU->RASR = (MPU_REGION_FULL_ACCESS) |  // Full Access (RW for both
                                          // privileged and unprivileged)
              MPU_REGION_SIZE_2MB |       // 2MB size
              (1 << MPU_RASR_ENABLE_Pos); // Enable region

  // Region 1: SRAM (RW)
  MPU->RNR = 1;                           // Select Region 0
  MPU->RBAR = SRAM_ORIGIN;                // Base Address
  MPU->RASR = (MPU_REGION_FULL_ACCESS) |  // Full Access (RW for both
                                          // privileged and unprivileged)
              MPU_REGION_SIZE_128KB |     // 128KB size
              (1 << MPU_RASR_ENABLE_Pos); // Enable region


  // Region 2: Peripheral (RW)
  MPU->RNR = 2;                           // Select Region 0
  MPU->RBAR = PERIPHERAL_ORIGIN;          // Base Address
  MPU->RASR = (MPU_REGION_READ_ONLY) |    // Privileged RW, unprivileged RO
              MPU_REGION_SIZE_64MB |      // 64MB size
              (1 << MPU_RASR_ENABLE_Pos); // Enable region

  // Region 3: Flash mapped to 0x00000000 (Code/RO)
  MPU->RNR = 3;                           // Select Region 0
  MPU->RBAR = 0x00000000;                 // Base Address
  MPU->RASR = (MPU_REGION_FULL_ACCESS) |  // Full Access (RW for both
                                          // privileged and unprivileged)
              MPU_REGION_SIZE_2MB |       // 2MB size
              (1 << MPU_RASR_ENABLE_Pos); // Enable region */

  //region 4: sram from 0x2002 0000
  MPU->RNR = 4;                           // Select Region 0
  MPU->RBAR = 0x20020000;                 // Base Address
  MPU->RASR = (MPU_REGION_FULL_ACCESS) |  // Full Access (RW for both
                                          // privileged and unprivileged)
              MPU_REGION_SIZE_64KB |     // 128KB size
              (1 << MPU_RASR_ENABLE_Pos); // Enable region

  // Enable the MPU with default memory map for privileged mode
  MPU->CTRL =
      (1 << MPU_CTRL_PRIVDEFENA_Pos) | // Default memory map for privileged mode
      (1 << MPU_CTRL_ENABLE_Pos);      // Enable MPU
}

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=28&zoom=100,89,117
