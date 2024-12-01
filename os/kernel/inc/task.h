#ifndef TASK_H
#define TASK_H

#define TASK_INVALID_ID_STATE (uint32_t)0
#define TASK_READY_STATE (uint32_t)1
#define TASK_BLOCKED_STATE (uint32_t)2

#include <stdint.h>

typedef struct {
  uint32_t psp_value;
  uint32_t current_state;
  uint32_t block_count;
  void (*task_handler)(void);
} TCB_t;

uint32_t osTaskCreate(void (*osTCB_task)(void));
void task_delay(uint32_t tick_count);
void osGetNextTask(void);
void osInitalizeTCB(void);
void osDeleteThread();
void osCheckBlockedTasks();
void idleTask(void);
uint32_t getTasksCount();

#endif // TASK_H