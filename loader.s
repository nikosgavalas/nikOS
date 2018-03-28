global loader

MAGIC_NUMBER	equ 0x1BADB002
FLAGS			equ 0x0
CHECKSUM		equ -MAGIC_NUMBER

section .text:

align 4
	dd	MAGIC_NUMBER
	dd	FLAGS
	dd	CHECKSUM

loader:                             ; linker entry point
	mov	eax, 0xCAFEBABE             ; magic number

loop:
	jmp	loop