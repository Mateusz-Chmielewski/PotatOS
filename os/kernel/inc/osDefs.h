#ifndef OS_DEFS_H
#define OS_DEFS_H

#define SRAM_START 0x20000000U
#define SRAM_SIZE (112U * 1024U)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define INNTERRUPT_DISABLE() __asm volatile("CPSID I")
#define INNTERRUPT_ENABLE() __asm volatile("CPSIE I")

#define TASK_STACK_SIZE 1024 // Size of the task stack
#define MAX_TASKS 10
#define TASK_STACK_SIZER 4096U

#endif // OS_DEFS_H
