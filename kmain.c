#include "drivers/framebuffer.h"

void kmain() {
	fb_clear();

	char *my_str = "Hello";
	int len = 5;
	fb_write(my_str, len);

	char *str = " World";
	fb_puts(str);

	return;
}
