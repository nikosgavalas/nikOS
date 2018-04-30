#include <mm/paging.h>

/* See https://wiki.osdev.org/Paging */

/* Page Dir Entry Flags */
#define PAGE_SIZE_4MiB  1 << 7
#define CACHE_DISABLE   1 << 4
#define WRITE_THROUGH   1 << 3
#define ACCESS_BY_ALL   1 << 2
#define READ_WRITE      1 << 1
#define PAGE_PRESENT    1

/* Page Table Entry Flags (in addition to the above) */
#define PREVENT_TLB_UPDATE 1 << 8

typedef unsigned int page_dir_entry;
typedef unsigned int page_table_entry;

page_dir_entry mk_page_dir_entry(unsigned int addr, unsigned char avail, unsigned int flags)
{
	/* avail currently not used */
	page_dir_entry ret = 0;
	
	addr &= 0xfffff000;
	ret |= addr;
	
	flags &= 0b110111111;
	ret |= flags;
	
	return ret;
}

page_dir_entry page_dir[1024];

page_table_entry mk_page_table_entry(unsigned int addr, unsigned char avail, unsigned int flags)
{
	/* avail currently not used */
	page_table_entry ret = 0;

	addr &= 0xfffff000;
	ret |= addr;

	flags &= 0b101111111;
	ret |= flags;

	return ret;
}

page_table_entry page_table[1024];

void paging_init()
{
	/* Initialize page directory */
	page_dir[0] = mk_page_dir_entry();
	
	/* Initialize page table */
	for (int i = 0; i < 1024; i++) {
		page_table[i] = mk_page_table_entry();
	}

	/* S = 0 (4KiB pages), A = 0 (indifferent), D = 1 (page caching enabled),
	 * W = 0 (write back), U = 0 (page dir entry only accessible by superuser),
	 * R = 1 (read/write page), P = 1 (present)
	 */
}
