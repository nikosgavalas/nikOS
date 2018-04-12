#include "drivers/framebuffer.h"
#include "drivers/serial.h"

void kmain() {
	fb_clear();
	serial_init_port(SERIAL_BASE_COM1, 1);

	char *my_str = "Hello";
	int len = 5;
	fb_write(my_str, len);

	char *str = " World";
	fb_puts(str);

	serial_write(SERIAL_BASE_COM1, "hei boi", 7);

	return;
}
