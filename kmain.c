#include "drivers/framebuffer.h"

void kmain() {
	fb_clear();

	char *my_str = "Hello";
	int len = 5;
	write(my_str, len);

	char *str = " World";
	puts(str);

	return;
}

