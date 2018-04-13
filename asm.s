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
