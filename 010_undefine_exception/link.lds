SECTIONS {
	. = 0x30000000;
	code_start = .;
	. = ALIGN(4);
	.text  : 
	{
		start.o(.text)
		*(.text) 
	}
	
	. = ALIGN(4);
	.rodata  : 
	{
		*(.rodata) 
	}
	
	. = ALIGN(4) ;
	.data :
	{
		*(.data) 
	}
	. = ALIGN(4) ;
	.bss : 
	{
		bss_start = . ;
		*(.bss) *(.COMMON)
	}
	end = .;
}