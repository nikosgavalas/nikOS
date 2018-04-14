#include "../asm/desc_tables.h"
#include "idt.h"

struct idt_entry {
	unsigned short offset_high;
	unsigned short flags;
	unsigned short segment_selector;
	unsigned short offset_low;
} __attribute__((packed));

struct idt_entry idt[256];

// asm_load_idt((void *) &idt);
