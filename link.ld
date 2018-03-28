ENTRY(loader)

SECTIONS {
	. = 0x00100000;            /* the code should be loaded at 1MiB,
	                              because lower addresses are used by GRUB */

	.text ALIGN (0x1000) :     /* align at 4KiB */
	{
		*(.text)               /* all text sections from all files */
	}

	.rodata ALIGN (0x1000) :
	{
		*(.rodata*)
	}

	.data ALIGN (0x1000) :
	{
		*(.data)
	}

	.bss ALIGN (0x1000) :
	{
		*(COMMON)
		*(.bss)
	}
}