#include "system/gdt.h"
#include "system/idt.h"

#include "drivers/serial.h"
#include "drivers/framebuffer.h"

#include "util/logger.h"

#include "interrupts.h"

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

	log(CONSOLE, INFO, "Installing the Interrupt Descriptor Table...");
	idt_install();

	fb_puts(welcome);

	interrupt(89);

	return;
}
