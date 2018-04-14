%macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
	push	dword 0                     ; push 0 as error code
	push	dword %1                    ; push the interrupt number
	jmp		common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
	push	dword %1                    ; push the interrupt number
	jmp		common_interrupt_handler    ; jump to the common handler
%endmacro

extern interrupt_handler

common_interrupt_handler:
	pushad		; push all (32-bit) general purpose regs (eax, ebx, ecx, edx, edi, esi, esp, ebp)

	call interrupt_handler

	popad		; pop all general purpose regs

	add	esp, 8	; restore the esp (because we pushed the interrupt number too, in the macro)

	iret
