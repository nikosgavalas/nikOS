#include "interrupt.h"
#include "asm.h"

#include "drivers/framebuffer.h" // REMOVE later

/* Causes a software interrupt */
void sw_interrupt() 
{
	asm_sw_interrupt();
}

struct cpu_state {
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
	unsigned int ebx;
	unsigned int edx;
	unsigned int ecx;
	unsigned int eax;
} __attribute__((packed));

/* The interrupt handler */
void interrupt_handler(struct cpu_state cpu, unsigned int int_num, unsigned int err)
{
	fb_puts("Inside handler\n");
}