#include "serial.h"
#include "../asm.h"

/* The serial ports use I/O ports, for configuration.
 * All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different base values.
 */
#define SERIAL_PORT_DATA(base)          (base)
#define SERIAL_PORT_FIFO_COMMAND(base)  (base + 2)
#define SERIAL_PORT_LINE_COMMAND(base)  (base + 3)
#define SERIAL_PORT_MODEM_COMMAND(base) (base + 4)
#define SERIAL_PORT_LINE_STATUS(base)   (base + 5)

/* I/O port command: Tells the serial port to expect first the highest 8 bits 
 * on the data port, then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/* Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
	outb(SERIAL_PORT_LINE_COMMAND(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_PORT_DATA(com), (divisor >> 8) & 0x00FF);
	outb(SERIAL_PORT_DATA(com), divisor & 0x00FF);
}

/* The port is set to have a data length of 8 bits, 
 * no parity bits, one stop bit and break control
 * disabled:
 */
void serial_configure_line(unsigned short com) 
{
	outb(SERIAL_PORT_LINE_COMMAND(com), 0x03);
}

/* The value 0xc7 here:
 * enables FIFO, clears both receiver and transmission FIFO queues,
 * and sets the size of the queue to 14 bytes
 */
void serial_configure_buffers(unsigned short com) 
{
	outb(SERIAL_PORT_FIFO_COMMAND(com), 0xc7);
}

/* Sets the Ready To Transmit (RTS) and Data Terminal Ready (DTR) pins to 1,
 * which means that the port is ready to send data.
 */
void serial_configure_modem(unsigned short com)
{
	outb(SERIAL_PORT_MODEM_COMMAND(com), 0x03);
}

/* To write to a serial port, we need to know that all previous writes are 
 * finished. To see if the FIFO queue is empty, we can "query" the serial port
 * and check the bit 5 of the status byte */
int serial_transmit_fifo_is_empty(unsigned int com) 
{
	return inb(SERIAL_PORT_LINE_STATUS(com)) & 0x20;
}

void serial_init_port(unsigned short com, unsigned short divisor) 
{
	serial_configure_baud_rate(com, divisor);
	serial_configure_line(com);
	serial_configure_buffers(com);
	serial_configure_modem(com);
}

/* serial_write checks if the port buffers are empty first. 
 * If they are not, it will spin until they are, before attempting to
 * send any data to the port.
 */
int serial_write(unsigned short com, char *data, unsigned int len) 
{
	unsigned int i = 0;
	while (!serial_transmit_fifo_is_empty(com))
		;
	for (i = 0; i < len; i++) {
		outb(SERIAL_PORT_DATA(com), *data++);
	}
	return i;
}

void serial_puts(unsigned short com, char *data) 
{
	while (*data)
		serial_write(com, data++, 1);
}
