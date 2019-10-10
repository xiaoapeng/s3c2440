SECTIONS {
	.text   0  : 
	{
		start.o(.text)
		*(.text) 
	}
   
	.rodata ALIGN(4) : 
	{
		*(.rodata) 
		. = ALIGN(4) ;
	}

	.data 0x30000000 : AT(LOADADDR(.rodata)+SIZEOF(.rodata))
	{ 
		data_load_addr = LOADADDR(.data);
		data_start = . ;
		*(.data) 
		data_end = . ;
	}
   
	.bss ALIGN(4) : 
	{
		bss_start = . ;
		*(.bss) *(.COMMON)
		bss_end = . ;
	}
}