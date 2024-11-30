#include "task.h"
#include "osDefs.h"
#include "scb.h"
#include "systick.h"

TCB_t osTasks[MAX_TASKS];
int osCurrentTaks;

// context switch
__attribute((naked)) void pend_sv_handler(void) {
  __asm volatile(
      // disable interrupts
      "CPSID I \n"
      // save the context of the current task
      // get current task PSP
      "MRS R0, PSP \n" // mrs - move from special register to general register
      // adress docelowy z jest napierw zmiejszany
      //! oznacza że po zakonczeniu  operacji adres w rejesrze zostanie
      //! zauktualizoawny do ostatniego uzytego
      // adressu w pamieci
      "STMDB R0!, {R4-R11} \n" // save the registers R4-R11 stmdb - store
                               // multiple registers decrement before

      "PUSH {LR} \n" // push link register
      "BL osSavePSPValue \n"

      // retrieve contextr of next task
      // decide next task to run
      "BL osGetNextTask \n"

      // get next task psp value
      "BL osGetPSPValue \n"

      "POP {LR} \n" // pop link register

      // restore the context of the next task
      "LDMIA R0!, {R4-R11} \n" // load the registers R4-R11 ldmia - load
                               // multiple registers increment after
      // set the PSP of the next task
      "MSR PSP, R0 \n" // mrs - move from general register to special register
      "CPSIE I \n"     // enable interrupts

      "BX LR \n"); // branch to task psp lr value
}

uint32_t osTaskCreate(void (*osTCB_task)(void)) {
  uint32_t *pSP;
  extern long _estack;
  for (int i = 0; i < MAX_TASKS; i++) {
    if (osTasks[i].current_state == TASK_INVALID_ID_STATE) {
      osTasks[i].task_handler = osTCB_task;
      osTasks[i].current_state = TASK_READY_STATE;
      osTasks[i].psp_value = SRAM_END - (i + 1) * TASK_STACK_SIZE;
      pSP = (uint32_t *)osTasks[i].psp_value;
      pSP--; // xPSR
      *pSP = (uint32_t)0x01000000;
      pSP--;                                    // PC
      *pSP = (uint32_t)osTasks[i].task_handler; // address if the task
      pSP--;                                    // LR
      *pSP = (uint32_t)0xFFFFFFFD; // exc return code page 44 cortex m4

      // zero out R4-R11
      for (int j = 0; j < 13; j++) {
        pSP--;
        *pSP = 0;
      }

      osTasks[i].psp_value = (uint32_t)pSP;
      return i;
    }
  }
  return -1;
}

void task_delay(uint32_t tick_count) {
  // disable interrupts
  INNTERRUPT_DISABLE();

  if (osCurrentTaks) { // osCurrentTask == 0 means it is an idle task
    osTasks[osCurrentTaks].block_count = systick_get_ticks() + tick_count;
    osTasks[osCurrentTaks].current_state = TASK_BLOCKED_STATE;

    // trigger pendsv exception
    SCB->ICSR |= SCB_ICSR_PENDSVSET;
  }

  // enable interrupts
  INNTERRUPT_ENABLE();
}

void osGetNextTask(void) {
  for (int i = 0; i < MAX_TASKS; i++) {
    osCurrentTaks++;
    osCurrentTaks %= MAX_TASKS;
    if (osTasks[osCurrentTaks].current_state == TASK_READY_STATE &&
        osCurrentTaks != 0) { // skip idle task
      break;
    }
  }
}

void osInitalizeTCB(void) {
  for (int i = 0; i < MAX_TASKS; i++) {
    osTasks[i].current_state = TASK_INVALID_ID_STATE;
  }
}

void osDeleteThread() {
  osTasks[osCurrentTaks].current_state = TASK_INVALID_ID_STATE;

  // trigger PendSV context switch to another task
  SCB->ICSR |= SCB_ICSR_PENDSVSET;
}

uint32_t osGetPSPValue(void) { return osTasks[osCurrentTaks].psp_value; }

void osSavePSPValue(uint32_t psp_stack_addr) {
  osTasks[osCurrentTaks].psp_value = psp_stack_addr;
}

// unblock tasks if enought ticks have passed
void osCheckBlockedTasks() {
  for (int i = 0; i < MAX_TASKS; i++) {
    if (osTasks[i].current_state == TASK_BLOCKED_STATE) {
      if (osTasks[i].block_count == systick_get_ticks()) {
        osTasks[i].current_state = TASK_READY_STATE;
      }
    }
  }
}

void idleTask(void) {
  while (1)
    ;
}
