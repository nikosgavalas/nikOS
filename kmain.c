#include <descriptor_tables/gdt.h>
#include <descriptor_tables/idt.h>

#include <drivers/serial.h>
#include <drivers/framebuffer.h>
#include <drivers/pic.h>

#include <mm/paging.h>

#include <interrupt/handler.h>
#include <logger.h>


char *welcome  = ""
"        _ _     ___  ____  \n"
"  _ __ (_) | __/ _ \\/ ___| \n"
" | '_ \\| | |/ / | | \\___ \\ \n"
" | | | | |   <| |_| |___) |\n"
" |_| |_|_|_|\\_\\\\___/|____/ \n"
"";

/* Kernel Main */
// TODO: multiboot_info is a pointer to a specific struct. fix this
void kmain(unsigned int multiboot_magic, unsigned int multiboot_info)
{
	/* Clear the screen */
	fb_clear();

	klog(CONSOLE, INFO, "Installing the Global Descriptor Table...");
	gdt_install();

	klog(CONSOLE, INFO, "Initializing COM1 serial port...");
	serial_init_port(SERIAL_BASE_COM1, 1);

	klog(CONSOLE, INFO, "Installing the Interrupt Descriptor Table...");
	idt_install();

	fb_puts(welcome);

	/* Test the interrupts */
	//sw_interrupt();
	//klog(CONSOLE, DEBUG, "returned.");

	klog(CONSOLE, INFO, "Initializing PIC...");
	pic_init();

	//paging_init();

	// minprintf("%c", 's');

	/* At this point the kernel is activated only through interrupts */
	for (;;) {
		asm ("hlt");
	}

	return;
}
