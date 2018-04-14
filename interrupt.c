#include "interrupt.h"
#include "asm.h"

/* Causes a software interrupt */
void interrupt() 
{
	asm_interrupt_1_test();
}

/* Interrupt Handler */
void interrupt_handler() 
{
	asm_interrupt_handler_1_test();
}