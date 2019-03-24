#ifndef _GDT_H_INCLUDED_
#define _GDT_H_INCLUDED_

/* Format of the gdt table: https://wiki.osdev.org/Global_Descriptor_Table */
struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity; /* <-- this byte contains the flags too */
    unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr {
    unsigned short size;
    unsigned int offset;
} __attribute__((packed));

/* usage of this macro example: SEGMENT_SELECTOR(CODE_SEG) (use with gdt_segment_t) */
#define SEGMENT_SELECTOR(x) (sizeof(struct gdt_entry) * x)

typedef enum gdt_segment {
    NULL_SEG,
    CODE_SEG,
    DATA_SEG
} gdt_segment_t;

void gdt_install();

#endif  // _GDT_H_INCLUDED_