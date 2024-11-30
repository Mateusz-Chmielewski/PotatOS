#ifndef OS_H
#define OS_H

#include "scb.h"

#include "systick.h"
#include "task.h"
#include "uart.h"
#include <stdint.h>

extern uart_handle_t uart1;

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=51
// change initalize PSP value, and change SP to PSP
__attribute((naked)) void osSwitchSPToPSP(void) {
  __asm volatile(
      // initalize PSP
      "push {LR} \n" // save lr value on stack (osGetPSPValue can change it if
                     // it calls another function)
      "BL osGetPSPValue \n"
      "POP {LR} \n"    // restore lr value
      "MSR PSP, R0 \n" // move value from general register to special register
                       // (return value is in R0)

      // change SP to PSP using control register
      "MOV R0, #0x02 \n" // 0x02 - 10 in binary, set SPSEL bit to 1
      "MSR CONTROL, R0 \n"
      // LR here has the return address of the function that called this
      // function
      "BX LR \n"); // branch to whoever called this function
}

void nmi_handler(void) {
  usart_write(&uart1, (uint8_t *)"NMI\n", 4);
  while (1) {
  }
}

void hard_fault_handler(void) {
  usart_write(&uart1, (uint8_t *)"Hard fault\n", 11);
  while (1) {
  }
}

void bus_fault_handler(void) {
  usart_write(&uart1, (uint8_t *)"Bus fault\n", 10);
  while (1) {
  }
}

void usage_fault_handler(void) {
  usart_write(&uart1, (uint8_t *)"Usage fault\n", 12);
  while (1) {
  }
}

void osEnableProcessorFaults(void) {
  // Enable MemManage, BusFault, and UsageFault exceptions
  SCB->SHCSR |=
      SCB_SHCSR_MEMFAULTENA | SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_USGFAULTENA;

  // lower the priority of pendSV
  // the higher the value, the lower the priority
  SCB->SHPR3 |= BIT(20);
  SCB->SHPR3 |= BIT(21);
  SCB->SHPR3 |= BIT(22);
  SCB->SHPR3 |= BIT(23);
}

// not used in emulator
void clock_init(void) {
  // 8hz HSI
  /*  // Wlaczenie HSI, wpisanie wartosci 1
   RCC->CR |= BIT(0);

   while (!(RCC->CR & BIT(1)))
     ;

   // clear 2 first bytes
   // set HSI as clock source
   RCC->CFGR = (uint32_t)0x00000000;
   RCC->PLLCFGR = (uint32_t)0x24003010;
   RCC->CIR = 0x00000000; */
}

void initScheduler() {
  systick_init(FREQ / 1000); // Tick every 1 ms

  osTaskCreate(idleTask);
}

void startScheduler(void) {
  // switch to using PSP stack
  osSwitchSPToPSP();

  idleTask(); // run first task
}

#endif // OS_H