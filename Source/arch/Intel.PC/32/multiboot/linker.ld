ENTRY(Start)
SECTIONS
{
    . = 1M;
	StartProgram = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
		Text = .;
		*(.Multiboot)
		*(.text)
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
	    Data = .;
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
	    BSS = .;
		*(COMMON)
		*(.bss)
	}
	EndProgram = .;
}
