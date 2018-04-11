#include "drivers/framebuffer.h"

void kmain() {
	fb_write_cell(25*80 - 1, 'A', FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);
	fb_write_cell(81, 'B', FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);

	fb_write_cell_coord(24, 78, 'C', FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);
	
	fb_move_cursor(1999);
	return;
}

