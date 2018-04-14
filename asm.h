#ifndef _ASM_H_INCLUDED_
#define _ASM_H_INCLUDED_

/* Wrappers of the assembly 'out' and 'in' instructions for I/O
     */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

/* Wrappers of lgdt, lidt */
void asm_load_gdt(void *gdtp);
void asm_load_idt(void *idtp);

/* Wrapper of int */
void asm_interrupt_1_test();
void asm_interrupt_handler_1_test();

#endif // _ASM_H_INCLUDED_
