MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
  .text : { *(.text*) } > FLASH
  .data : { *(.data*) } > RAM
  .bss  : { *(.bss*)  } > RAM
}
