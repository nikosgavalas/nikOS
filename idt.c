#include "idt.h"
#include "asm.h"
#include "interrupt.h"
#include "system/gdt.h"

/* https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_IA-32 */
struct idt_entry {
	unsigned short offset_low;
	unsigned short segment_selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short offset_high;
} __attribute__((packed));

/* https://wiki.osdev.org/Interrupt_Descriptor_Table#Loading.2FStoring */
struct idt_ptr {
	unsigned short size;
	unsigned int offset;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void init_idt_entry(unsigned char num, unsigned int offset, 
                    unsigned short segment, unsigned char flags)
{
	idt[num].offset_high = (unsigned short) ((offset & 0xffff0000) >> 16);
	idt[num].offset_low = (unsigned short) (offset & 0x0000ffff);
	
	idt[num].segment_selector = segment;
	
	idt[num].zero = 0;
	idt[num].flags = flags;
}

void idt_install()
{
	for (unsigned int i = 0; i < 256; i++) {
		init_idt_entry((unsigned char) i, (unsigned int) &interrupt_handler,
		               SEGMENT_SELECTOR(CODE_SEG), 0b10001110);
	}

	idtp.size = (unsigned short) sizeof(idt) - 1;
	idtp.offset = (unsigned int) &idt;

	asm_load_idt((void *) &idtp);
}
