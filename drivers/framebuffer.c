#include "io.h"
#include "framebuffer.h"

char *fb = (char *)FB_BASE_ADDR;

void fb_write_cell(unsigned int pos, char c, unsigned char fg, unsigned char bg) {
	if (pos < FB_MAX_POS) {
		unsigned int i = pos * 2;
		fb[i] = c;
		fb[i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
	}
}

void fb_move_cursor(unsigned short pos) {
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	outb(FB_PORT_DATA, (unsigned char) (pos & 0xff00) >> 8);
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	outb(FB_PORT_DATA, (unsigned char) pos & 0x00ff);
}

void fb_write_cell_coord(unsigned int row, unsigned int col, 
                         char c, unsigned char fg, unsigned char bg) {
	if (row < FB_ROWS && col < FB_COLS) {
		fb_write_cell(row * 80 + col, c, fg, bg);
	}
}
