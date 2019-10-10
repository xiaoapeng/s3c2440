SECTIONS {
   .text   0  : 
   {
   	start.o(.text)
   	*(.text) 
   }
   
   .rodata  : { *(.rodata) }
   
   .data 0x30000000 : AT(LOADADDR(.rodata)+SIZEOF(.rodata))
   { 
      data_load_addr = LOADADDR(.data);
      data_start = . ;
      *(.data) 
      data_end = . ;
   }
   
   .bss  : { *(.bss) *(.COMMON) }
}