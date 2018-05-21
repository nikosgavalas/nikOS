; See https://wiki.osdev.org/Bare_Bones
; and https://wiki.osdev.org/Higher_Half_bare_bones , lots of stuff taken from there

global loader
extern kmain

; Multiboot header - see GRUB docs for details
MODULEALIGN			equ	1 << 0                      ; align loaded modules on page boundaries
MEMINFO				equ	1 << 1                      ; provide memory map
FLAGS				equ	MODULEALIGN | MEMINFO
MAGIC				equ 0x1badb002
CHECKSUM			equ	-(MAGIC + FLAGS)            ; CHECKSUM + MAGIC should equal FLAGS

; Taken from OsDev Wiki:
; Virtual base address of kernel space, used to convert virtual
; addresses into physical addresses until paging is enabled -- the amount that must
; be subtracted from a virtual address to get a physical address.
KERNEL_VIRTUAL_BASE	equ 0xC0000000                  ; 3GiB
KERNEL_PAGE_NUMBER	equ (KERNEL_VIRTUAL_BASE >> 22) ; Page directory index of kernel's 4MiB PTE.

KERNEL_STACK_SIZE	equ 0x4000                      ; initial kernel stack size is 16k

section .data
align 0x1000                                        ; align at 4kiB
boot_page_directory:
	; Taken from OsDev Wiki:
	; This page directory entry identity-maps the first 4MiB of the 32-bit physical address space.
	; All bits are clear except the following:
	; bit 7: PS The kernel page is 4MiB.
	; bit 1: RW The kernel page is read/write.
	; bit 0: P  The kernel page is present.
	; This entry must be here -- otherwise the kernel will crash immediately after paging is
	; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
	dd 0x00000083
	times (KERNEL_PAGE_NUMBER - 1) dd 0             ; Pages before kernel space.
	; This page directory entry defines a 4MiB page containing the kernel.
	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0      ; Pages after the kernel image.
 
section .text
align 4
multiboot_header:
	dd	MAGIC
	dd	FLAGS
	dd	CHECKSUM                                  


loader equ (_loader - KERNEL_VIRTUAL_BASE)          ; linker entry point
_loader:
	; Until paging is set up, the code must be position-independent and use physical
    ; addresses, not virtual ones

	mov	ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)  	; the address of the page directory
	mov	cr3, ecx

	mov	ecx, cr4
	or	ecx, 0x00000010   ; Set PSE bit in CR4 to enable 4MiB pages.
	mov	cr4, ecx

	mov	ecx, cr0         ; set the "paging-enable" and "protection" bits of CR0.
	or	ecx, 0x80000001  ; note: setting the paging flag when the protection flag is clear 
	                     ; causes a general-protection exception. 
	mov	cr0, ecx

	; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of higher_half_entry which is
    ; approximately 0xC0100000.
    lea	ecx, [higher_half_entry]
    jmp	ecx                                       ; NOTE: Must be absolute jump!
	
higher_half_entry:
	; Unmap the identity-mapped first 4MiB of physical address space. It should not be needed
	; anymore.
	mov	dword [boot_page_directory], 0
	invlpg	[0]  ; invalidates a single page on the TLB.
	             ; note: this only invalidates the page on the current processor
				 ; (if you go multicore you need to do some other stuff too)

	mov	esp, kernel_stack + KERNEL_STACK_SIZE     ; point esp to the end of the kernel stack
	push eax     ; pass the multiboot magic number
	add	ebx, KERNEL_VIRTUAL_BASE
    push ebx     ; pass multiboot info structure -- WARNING: This is a 
	             ; physical address and may not be in the first 4MiB
	call kmain
	hlt                                           ; unreachable (kmain should never return)

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE                        ; reserve stack for the kernel
