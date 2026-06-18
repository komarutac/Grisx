ENTRY(Start)
SECTIONS
{
    . = 2M;
	StartProgram = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
		StartText = .;
		*(.Multiboot)
		*(.text)
		*(.rodata)
		EndText = .;
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
	    StartData = .;
		*(.data)
		EndData = .;
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
	    StartBSS = .;
		*(COMMON)
		*(.bss)
		EndBSS = .;
	}
	EndProgram = .;
}
