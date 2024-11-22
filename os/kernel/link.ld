ENTRY(_reset);
MEMORY {
  flash(rx)  : ORIGIN = 0x08000000, LENGTH = 1024k
  sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128k
}
_estack     = ORIGIN(sram) + LENGTH(sram);    /* stack points to end of SRAM */

SECTIONS {
  .vectors  : { KEEP(*(.vectors)) }   > flash /* Place in flash memory */
  .text     : { *(.text*) }           > flash /* Place in flash memory */
  .rodata   : { *(.rodata*) }         > flash /* Place in flash memory */

  .data : {
    _sdata = .;   /* .data section start */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = .;  /* .data section end */
  } > sram AT > flash
  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;              /* .bss section start */
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;              /* .bss section end */
  } > sram

  . = ALIGN(8);
  _end = .;     /* for cmsis_gcc.h  */
}