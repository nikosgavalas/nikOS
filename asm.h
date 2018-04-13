#ifndef _ASM_H_INCLUDED_
#define _ASM_H_INCLUDED_

/* Wrappers of the assembly 'out' and 'in' instructions for I/O
 */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

void asm_load_gdt(void *gdtp);

#endif // _ASM_H_INCLUDED_
