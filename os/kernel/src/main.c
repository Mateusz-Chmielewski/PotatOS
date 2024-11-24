// Startup code
#include "systick.h"
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "common.h"
#include "utils.h"
#include "mpu.h"
#include "control.h"
#include "system_calls.h"
#include "scb.h"

static uint8_t greet[] = "Hello in kernel!\n";

uart_handle_t uart1 = {UART1, 0};
uart_handle_t uart2 = {UART2, 0};
uart_handle_t uart3 = {UART3, 0};

#define TASK_STACK_SIZE 1024 // Size of the task stack in words (adjust as needed)

void nmi_handler(void)
{
  // write to usart message of exception
  usart_write(&uart1, (uint8_t *)"NMI\n", 4);
  while (1)
  {
  }
}

void hard_fault_handler(void)
{
  // write to usart message of exception
  usart_write(&uart1, (uint8_t *)"Hard fault\n", 11);
  while (1)
  {
  }
}

void osEnableProcessorFaults(void)
{
  // Enable MemManage, BusFault, and UsageFault exceptions
  // SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA | SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_USGFAULTENA;

  // lower the priority of pendSV
  // the higher the value, the lower the priority
  SCB->SHPR3 |= BIT(20);
  SCB->SHPR3 |= BIT(21);
  SCB->SHPR3 |= BIT(22);
  SCB->SHPR3 |= BIT(23);
}

// https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=51

// context switch
__attribute((naked)) void pend_sv_handler(void)
{

  /* char *msg = "pend sv handler\n";
  usart_write(&uart1, msg, length(msg)); */
  __asm volatile(
      // disable interrupts
      "CPSID I \n"
      // save the context of the current task
      // get current task PSP
      "MRS R0, PSP \n" // mrs - move from special register to general register
      // adress docelowy z jest napierw zmiejszany
      //! oznacza że po zakonczeniu  operacji adres w rejesrze zostanie zauktualizoawny do ostatniego uzytego
      // adressu w pamieci
      "STMDB R0!, {R4-R11} \n" // save the registers R4-R11 stmdb - store multiple registers decrement before

      "PUSH {LR} \n" // push link register
      "BL osSavePSPValue \n"

      // retrieve contextr of next task
      // decide next task to run
      "BL osGetNextTask \n"

      // get next task psp value
      "BL osGetPSPValue \n"

      "POP {LR} \n" // pop link register

      // restore the context of the next task
      "LDMIA R0!, {R4-R11} \n" // load the registers R4-R11 ldmia - load multiple registers increment after
      // set the PSP of the next task
      "MSR PSP, R0 \n" // mrs - move from general register to special register
      "CPSIE I \n"

      "BX LR \n"); // branch to whoever called this function
}

// change initalize PSP value, and change SP to PSP
__attribute((naked)) void osSwitchSPToPSP(void)
{
  __asm volatile(
      // initalize PSP
      "push {LR} \n" // save lr value on stack (osGetPSPValue can change it if it calls another function)
      "BL osGetPSPValue \n"
      "POP {LR} \n"    // restore lr value
      "MSR PSP, R0 \n" // move value from general register to special register (return value is in R0)

      // change SP to PSP using control register
      "MOV R0, #0x02 \n" // 0x02 - 10 in binary, set SPSEL bit to 1
      "MSR CONTROL, R0 \n"
      "BX LR \n"); // branch to whoever called this function
}

#define TASK_INVALID_ID_STATE 0
#define TASK_READY_STATE 1
#define TASK_BLOCKED_STATE 2

#define MAX_TASKS 10
#define TASK_STACK_SIZER 4096U
typedef struct
{
  uint32_t osTCB_PSPValue;
  uint32_t osTCB_CURRENTState;
  uint32_t osTCB_BlockCount;
  void (*osTCB_Task)(void);
} osTaskControlBlock_t;

osTaskControlBlock_t osTaskControlBlock[MAX_TASKS];
int osCurrentTaks;

uint32_t osGetPSPValue(void)
{
  return osTaskControlBlock[osCurrentTaks].osTCB_PSPValue;
}

void osSavePSPValue(uint32_t psp_stack_addr)
{
  osTaskControlBlock[osCurrentTaks].osTCB_PSPValue = psp_stack_addr;
}

void osGetNextTask(void)
{
  for (int i = 0; i < MAX_TASKS; i++)
  {
    osCurrentTaks++;
    osCurrentTaks %= MAX_TASKS;
    if (osTaskControlBlock[osCurrentTaks].osTCB_CURRENTState == TASK_READY_STATE)
    {
      break;
    }
  }
}

void osInitalieTCK(void)
{
  for (int i = 0; i < MAX_TASKS; i++)
  {
    osTaskControlBlock[i].osTCB_CURRENTState = TASK_INVALID_ID_STATE;
  }
}

#define SRAM_START 0x20000000U
#define SRAM_SIZE (112U * 1024U)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

uint32_t osCreateThread(void (*osTCB_task)(void))
{
  uint32_t *pSP;
  extern long _estack;
  for (int i = 0; i < MAX_TASKS; i++)
  {
    if (osTaskControlBlock[i].osTCB_CURRENTState == TASK_INVALID_ID_STATE)
    {
      osTaskControlBlock[i].osTCB_Task = osTCB_task;
      osTaskControlBlock[i].osTCB_CURRENTState = TASK_READY_STATE;
      osTaskControlBlock[i].osTCB_PSPValue = SRAM_END - (i + 4) * TASK_STACK_SIZE;
      pSP = (uint32_t *)osTaskControlBlock[i].osTCB_PSPValue;
      pSP--; // xPSR
      *pSP = (uint32_t)0x01000000;
      pSP--; // PC
      *pSP = (uint32_t)osTaskControlBlock[i].osTCB_Task;
      pSP--; // LR
      *pSP = (uint32_t)0xFFFFFFFD;

      // zero out R4-R11
      for (int j = 0; j < 13; j++)
      {
        pSP--;
        *pSP = 0;
      }

      osTaskControlBlock[i].osTCB_PSPValue = (uint32_t)pSP;
      return i;
    }
  }
  return -1;
}

void osDeleteThread()
{
  osTaskControlBlock[osCurrentTaks].osTCB_CURRENTState = TASK_INVALID_ID_STATE;

  // trigger PendSV context switch to another task
  SCB->ICSR |= SCB_ICSR_PENDSVSET;
}

static volatile uint64_t s_ticks = 0;

static volatile uint64_t current = 0;

// FREQ/1000 - Tick every 1 ms so s_ticks will be incremented every 1 ms
// 1 second = 1000 ms, so 1000 ms / 1 ms = 1000 ticks

void sys_tick_handler(void)
{
  s_ticks++;

  // unblock tasks
  for (int i = 0; i < MAX_TASKS; i++)
  {
    if (osTaskControlBlock[i].osTCB_CURRENTState == TASK_BLOCKED_STATE)
    {
      if (osTaskControlBlock[i].osTCB_BlockCount == s_ticks)
      {
        osTaskControlBlock[i].osTCB_CURRENTState = TASK_READY_STATE;
      }
    }
  }

  /* // swtich task every 1s
  if (s_ticks - current > 1000)
  {
    current = s_ticks;
    SCB->ICSR |= SCB_ICSR_PENDSVSET;
  } */

  SCB->ICSR |= SCB_ICSR_PENDSVSET;
}

uint64_t systick_get_ticks(void)
{
  return s_ticks;
}

void osDelay(uint32_t tick_count)
{
  if (osCurrentTaks)
  { // osCurrentTask == 0 means it is an idle task
    osTaskControlBlock[osCurrentTaks].osTCB_BlockCount = systick_get_ticks() + tick_count;
    osTaskControlBlock[osCurrentTaks].osTCB_CURRENTState = TASK_BLOCKED_STATE;

    // trigger pendsv exception
    SCB->ICSR |= SCB_ICSR_PENDSVSET;
  }
}

void task1(void)
{
  char *msg = "Task 1 -- ";
  char msg2[2] = {'a', '\n'};

  while (1)
  {
    usart_write(&uart1, (uint8_t *)msg, length(msg));
    usart_write(&uart1, (uint8_t *)msg2, 2);

    msg2[0]++;
    if (msg2[0] > 'z')
    {
      msg2[0] = 'a';
    }
    osDelay(1000);
  }
}

void task2(void)
{

  char *msg = "Task 2 -- ";
  char msg2[2] = {'0', '\n'};

  while (1)
  {
    usart_write(&uart3, (uint8_t *)msg, length(msg));
    usart_write(&uart3, (uint8_t *)msg2, 2);

    msg2[0]++;

    if (msg2[0] > '9')
    {
      msg2[0] = '0';
    }
    osDelay(2000);
  }
}

void idleTask(void)
{

  char *msg = "idle task\n";

  usart_write(&uart1, (uint8_t *)msg, length(msg));

  while (1)
  {
    echo(&uart2);
  };
}

int main(void)
{

  // SCB->CCR = SCB->CCR | 0x200;
  rcc_gpioa_enable();
  rcc_usart1_enable();
  rcc_usart2_enable();
  rcc_usart3_enable();

  uart_init(&uart1, 9600U);
  uart_init(&uart2, 9600U);
  uart_init(&uart3, 9600U);

  usart_write(&uart1, greet, length(greet));

  osEnableProcessorFaults();
  osInitalieTCK();

  osCreateThread(idleTask);
  osCreateThread(task1);
  osCreateThread(task2);

  systick_init(FREQ / 1000); // Tick every 1 ms

  osSwitchSPToPSP();

  idleTask();
  // usart_syscall_write(greet3, length(greet3));
  // mpu_init();
  // usart_syscall_write(&x, 1);
  // start_task(task1);

  while (1)
    ;
  return 0;
}
