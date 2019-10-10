SECTIONS {
	. = 0x0;
	.text 		ALIGN(4) : { 
	start.o(.text)
	main.o(.text)
	*(.text)
	}

	
	.rodata 	ALIGN(4) :{ *(.rodata*) }
	
	.data 0x30000000  : AT(0x2000) 
	{
		data_load_addr = LOADADDR(.data);
		data_start = .;
		*(.data*) 
		data_end = .;
	}

	
	.bss 		ALIGN(4) : { *(.bss) *(COMMON) }
}
