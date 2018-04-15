#include "interrupt.h"
#include "asm.h"

#include "util/logger.h"

/* Causes a software interrupt */
void sw_interrupt() 
{
	asm_sw_interrupt();
}

void interrupt_handler()
{
	log(CONSOLE, INFO, "inside handler");
}