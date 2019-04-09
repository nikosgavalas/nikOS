#include <descriptors/gdt.h>
#include <descriptors/idt.h>

#include <drivers/framebuffer.h>
#include <drivers/pic.h>
#include <drivers/serial.h>

#include <interrupt/handler.h>
#include <lib/logger.h>

char *welcome =
    ""
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

    /* Test the interrupts */
    // sw_interrupt();
    // log(CONSOLE, DEBUG, "returned.");

    log(CONSOLE, INFO, "Initializing PIC...");
    pic_init();

    /* At this point the kernel is activated only through interrupts */
    for (;;) {
        asm("hlt");
    }

    return;
}
