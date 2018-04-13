#include "drivers/framebuffer.h"
#include "drivers/serial.h"
#include "gdt.h"

void kmain() {
	/* Clear the screen */
	fb_clear();

	/* Initialize COM1 serial port */
	serial_init_port(SERIAL_BASE_COM1, 1);

	gdt_install();

	return;
}
