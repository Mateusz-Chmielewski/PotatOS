#include "vector.h"

// naked - do not generate prologue/epilogue sequences for function
// noreturn - function does not return
//__attribute__((naked, noreturn))
void _reset(void)
{
  // extern variables from linker script
  extern long _sbss, _ebss, _sdata, _edata, _sidata;

  // zero bss .section
  for (long *dst = &_sbss; dst < &_ebss; dst++)
    *dst = 0;

  // copy .data section from flash to ram
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
    *dst++ = *src++;

  extern int main(void);
  (void)main();

  while (1)
  {
  };
}

extern unsigned _estack;

// define the vector table in the .vectors section
// contains 16+82 pointers to functions (interrupt handlers)
__attribute__((section(".vectors"))) vector_table_t vector_table = {
    .initial_sp_value = &_estack,
    .reset = _reset,
    .nmi = nmi_handler,
    .hard_fault = hard_fault_handler,
    .mem_manage = mem_manage_handler,
    .sv_call = sv_call_handler,
    .pend_sv = pend_sv_handler,
    .systick = sys_tick_handler,
    .irq = {
        IRQ_HANDLERS}};