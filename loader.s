global loader

extern kmain

MAGIC_NUMBER		equ 0x1BADB002
FLAGS				equ 0x0
CHECKSUM			equ -MAGIC_NUMBER

KERNEL_STACK_SIZE	equ 4096

section .text
align 4
	dd	MAGIC_NUMBER
	dd	FLAGS
	dd	CHECKSUM                                  ; CHECKSUM + MAGIC_NUMBER should equal FLAGS

loader:                                           ; linker entry point
	mov eax, 0xCAFEBABE
	mov	esp, kernel_stack + KERNEL_STACK_SIZE     ; point esp to the end of the kernel stack

	call kmain
loop:
	jmp loop

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE                       ; reserve stack for the kernel
