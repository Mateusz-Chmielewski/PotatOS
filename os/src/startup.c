#include "main.h"
#include "systick.h"

// naked - do not generate prologue/epilogue sequences for function
// noreturn - function does not return
__attribute__((naked, noreturn)) void _reset(void)
{
  // extern variables from linker script
  extern long _sbss, _ebss, _sdata, _edata, _sidata;

  // zero bss .section
  for (long *dst = &_sbss; dst < &_ebss; dst++)
    *dst = 0;

  // copy .data section from flash to ram
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
    *dst++ = *src++;

  main();

  while (1)
  {
  };
}

extern void _estack(void); // Defined in link.ld

// define the vector table in the .vectors section
// contains 16+82 pointers to functions (interrupt handlers)
__attribute__((section(".vectors"))) void (*const tab[16 + 82])(void) = {

    _estack, // stack pointer
    _reset,  // reset handler
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    Systick_Handler, // systick handler
};