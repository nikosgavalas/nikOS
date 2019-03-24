ENTRY(loader)
OUTPUT_FORMAT(elf32-i386) 

SECTIONS {
    /* The kernel will live at 3GB + 1MB in the virtual
     * address space, which will be mapped to 1MB in the
     * physical address space. */
    . = 0xC0100000;

    .text ALIGN (0x1000) : AT(ADDR(.text) - 0xC0000000)    /* align at 4KiB */
    {
        *(.text)               /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss) - 0xC0000000)
    {
        *(COMMON)
        *(.bss)
    }
}
