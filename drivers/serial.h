#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

/* COMx base ports */
#define SERIAL_BASE_COM1 0x3f8
#define SERIAL_BASE_COM2 0x2f8
#define SERIAL_BASE_COM3 0x3e8
#define SERIAL_BASE_COM4 0x2e8

void serial_init_port(unsigned short com, unsigned short divisor);
int serial_write(unsigned short com, char *data, unsigned int len);
void serial_puts(unsigned short com, char *data);

#endif  // _SERIAL_H_INCLUDED
