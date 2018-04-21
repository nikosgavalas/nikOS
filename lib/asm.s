; All the wrappers use the 'cdecl' calling standard

; outb - send a byte to the given I/O port
global outb    ; make visible to the linker
outb:
	mov	al, [esp + 8]    ; data to write to the i/o port
	mov	dx, [esp + 4]    ; address of the i/o port
	out	dx, al
	ret

; inb - returns a byte from the given I/O port
global inb
inb:
	mov dx, [esp + 4]    ; The address of the I/O port
	in  al, dx
	ret

; lgdt wrapper
global asm_load_gdt
asm_load_gdt:
	mov	eax, [esp + 4]
	lgdt	[eax]
	mov	ax, 0x10    ; i think GRUB has set all this registers inb4,
	mov	ds, ax      ; but I 'll do it anyway. 
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax
	jmp	0x08:flush  ; this finally sets the cs reg
flush:
	ret

; lidt wrapper
global asm_load_idt
asm_load_idt:
	mov	eax, [esp + 4]	; address of the idt
	lidt	[eax]
	ret

; int wrapper (causes a software interrupt)
global asm_sw_interrupt
asm_sw_interrupt:
	int	0x80
	ret

; sti wrapper
global asm_enable_interrupts
asm_enable_interrupts:
	sti
	ret

; cli wrapper
global asm_disable_interrupts
asm_disable_interrupts:
	cli
	ret
