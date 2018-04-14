#ifndef _IO_H_INCLUDED_
#define _IO_H_INCLUDED_

/* Wrappers of the assembly 'out' and 'in' instructions for I/O
 */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif // _IO_H_INCLUDED_