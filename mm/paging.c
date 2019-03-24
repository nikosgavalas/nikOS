#include <mm/paging.h>

/* See https://wiki.osdev.org/Paging */

#define FLAGS_BASE 0x00000000

/* Page Dir Entry Flags */
#define PAGE_SIZE_4MiB 1 << 7  /* 4KiB by default */
#define DISABLE_CACHING 1 << 4 /* enabled by default */
#define WRITE_THROUGH 1 << 3   /* write-back by default */
#define ACCESS_BY_ALL 1 << 2   /* only supervisor access by default */
#define READ_WRITE 1 << 1      /* read only by default */
#define PRESENT 1 << 0         /* if set, the page is actually in physical memory at the moment.             \
                                * When a page is swapped out, it is not in physical memory and therefore not \
                                * 'Present'. If a page is called, but not present, a page fault will occur */

/* Page Table Entry Flags (in addition to the above - yes they mostly use the same flags) */
#define PREVENT_TLB_UPDATE 1 << 8

typedef unsigned int page_dir_entry;
typedef unsigned int page_table_entry;

page_dir_entry mk_page_dir_entry(unsigned int addr, unsigned char avail, unsigned int flags) {
    /* avail currently not used */
    page_dir_entry ret = 0;

    addr &= 0xfffff000;
    ret |= addr;

    flags &= (unsigned int)0b110111111;
    ret |= flags;

    return ret;
}

page_dir_entry page_dir[1024];

/* I will not use the page table for now, only the page directory, because
 * I 've chosen my pagesize to be 4MiB instead of 4KiB, for simplicity */
page_table_entry mk_page_table_entry(unsigned int addr, unsigned char avail, unsigned int flags) {
    /* avail currently not used */
    page_table_entry ret = 0;

    addr &= 0xfffff000;
    ret |= addr;

    flags &= (unsigned int)0b101111111;
    ret |= flags;

    return ret;
}

page_table_entry page_table[1024];

void paging_init() {
    /* Initialize page directory */
    //page_dir[0] = mk_page_dir_entry(, , FLAGS_BASE | READ_WRITE);
}
