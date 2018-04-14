#include "system/gdt.h"
#include "drivers/serial.h"
#include "drivers/framebuffer.h"
#include "util/logger.h"

char *welcome  = ""
"        _ _     ___  ____  \n"
"  _ __ (_) | __/ _ \\/ ___| \n"
" | '_ \\| | |/ / | | \\___ \\ \n"
" | | | | |   <| |_| |___) |\n"
" |_| |_|_|_|\\_\\\\___/|____/ \n"
"";

/* Kernel Main */
void kmain() {
	/* Clear the screen */
	fb_clear();

	log(CONSOLE, INFO, "Installing the Global Descriptor Table...");
	gdt_install();

	log(CONSOLE, INFO, "Initializing COM1 serial port...");
	serial_init_port(SERIAL_BASE_COM1, 1);

	fb_puts(welcome);

	return;
}
