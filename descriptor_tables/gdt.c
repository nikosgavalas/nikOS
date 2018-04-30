#include <descriptor_tables/gdt.h>
#include <asm.h>

#define GDT_NUM_SEGMENTS 3

#define CODE_SEGMENT_BASE 0
#define CODE_SEGMENT_LIMIT 0xffffffff

#define DATA_SEGMENT_BASE 0
#define DATA_SEGMENT_LIMIT 0xffffffff

struct gdt_entry gdt[GDT_NUM_SEGMENTS];
struct gdt_ptr gdtp;

void gdt_init_segment(gdt_segment_t seg, unsigned long base, unsigned long limit, 
                      unsigned char access, unsigned char flags)
{
	gdt[seg].base_low = base & 0xffff;
	gdt[seg].base_middle = (base >> 16) & 0xff;
	gdt[seg].base_high = (base >> 24) & 0xff;

	gdt[seg].limit_low = limit & 0xffff;
	gdt[seg].granularity = (limit >> 16) & 0x0f;

	gdt[seg].granularity |= flags << 4;
	gdt[seg].access = access;
}

void gdt_install()
{

	/* NULL segment */
	gdt_init_segment(NULL_SEG, 0, 0, 0, 0);

	/* CODE segment: Base address is 0, limit = 4GiB. Values explanation:
	 * Access = 1001 1010: Pr = 1, Ring Level = 00, Ex = 1 (->CS)
	 *                     Conforming bit = 0 (segment is executable only from ring specified)
	 *                     RW = 1 (Read allowed for this CS)
	 *                     Ac = 0 (Managed by the CPU)
	 * Flags = 1100: Gr = 1 (4KiB page granularity)
	 *               Sz = 1 (32-bit protected mode)
	 */
	gdt_init_segment(CODE_SEG, CODE_SEGMENT_BASE, CODE_SEGMENT_LIMIT, 
	                 0b10011010, 0b00001100);

	/* Data segment: same as the CS, except Ex bit is 0 (->DS)
	 * With these configs in the DS -> the stack grows down,
	 * and also the DS is writable.
	 */
	gdt_init_segment(DATA_SEG, DATA_SEGMENT_BASE, DATA_SEGMENT_LIMIT, 
	                 0b10010010, 0b00001100);

	gdtp.size = sizeof(gdt) - 1;
	gdtp.offset = (unsigned int) &gdt;

	asm_load_gdt((void *) &gdtp);
}
