; wrappers for the assembly 'out' and 'in' instructions for I/O
; They use the 'cdecl' calling standard

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
            