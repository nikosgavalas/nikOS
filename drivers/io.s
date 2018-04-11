global outb    ; make visible to the linker

; uses the 'cdecl' calling standard
outb:
	mov	al, [esp + 8]    ; rightmost argument passed (data to write to the i/o port)
	mov	dx, [esp + 4]    ; second rightmost (address of the i/o port)
	out	dx, al
	ret