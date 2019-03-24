#include <asm.h>
#include <descriptor_tables/gdt.h>

#define GDT_NUM_SEGMENTS 3

#define CODE_SEGMENT_BASE 0
#define CODE_SEGMENT_LIMIT 0xffffffff

#define DATA_SEGMENT_BASE 0
#define DATA_SEGMENT_LIMIT 0xffffffff

#define ACCESS_BYTE_BASE 0x10
#define FLAGS_BASE 0x00

#define PRESENT 1 << 7
#define PRIVL_RING_3 3 << 5 /* default is ring 0 */
#define EXECUTABLE_SEG 1 << 3
#define DIRECTION_DOWN 1 << 2 /* use only for data segments */
#define CONFORMING_SEG 1 << 2 /* use only for code segments */
#define READABLE_SEG 1 << 1   /* use only for data segments */
#define WRITABLE_SEG 1 << 1   /* use only for code segments */
#define ACCESSED 1 << 1       /* the cpu manages this - read only */
#define PAGE_GRANULARITY 1 << 3
#define PROTECTED_32_BIT_MODE 1 << 2

struct gdt_entry gdt[GDT_NUM_SEGMENTS];
struct gdt_ptr gdtp;

void gdt_init_segment(gdt_segment_t seg, unsigned long base, unsigned long limit,
                      unsigned char access, unsigned char flags) {
    gdt[seg].base_low = base & 0xffff;
    gdt[seg].base_middle = (base >> 16) & 0xff;
    gdt[seg].base_high = (base >> 24) & 0xff;

    gdt[seg].limit_low = limit & 0xffff;
    gdt[seg].granularity = (limit >> 16) & 0x0f;

    gdt[seg].granularity |= flags << 4;
    gdt[seg].access = access;
}

void gdt_install() {
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
    unsigned char code_seg_access_byte = ACCESS_BYTE_BASE | PRESENT | EXECUTABLE_SEG | READABLE_SEG;
    unsigned char code_seg_flags = FLAGS_BASE | PAGE_GRANULARITY | PROTECTED_32_BIT_MODE;
    gdt_init_segment(CODE_SEG, CODE_SEGMENT_BASE, CODE_SEGMENT_LIMIT,
                     code_seg_access_byte, code_seg_flags);

    /* Data segment: same as the CS, except Ex bit is 0 (->DS)
   * With these configs in the DS -> the stack grows down,
   * and also the DS is writable.
   */
    unsigned char data_seg_access_byte = ACCESS_BYTE_BASE | PRESENT | WRITABLE_SEG;
    unsigned char data_seg_flags = FLAGS_BASE | PAGE_GRANULARITY | PROTECTED_32_BIT_MODE;
    gdt_init_segment(DATA_SEG, DATA_SEGMENT_BASE, DATA_SEGMENT_LIMIT,
                     data_seg_access_byte, data_seg_flags);

    gdtp.size = sizeof(gdt) - 1;
    gdtp.offset = (unsigned int)&gdt;

    asm_load_gdt((void *)&gdtp);
}
