#include "io.h"
#include "framebuffer.h"

#define FB_BASE_ADDR 0x000b8000

#define FB_PORT_COMMAND 0x3d4
#define FB_PORT_DATA 0x3d5

#define FB_COMMAND_HIGH_BYTE 14
#define FB_COMMAND_LOW_BYTE 15

char *fb = (char *) FB_BASE_ADDR;
unsigned short curr_pos = 0;

void fb_write_cell(unsigned int pos, char c, unsigned char fg, unsigned char bg) {
	pos *= 2;
	fb[pos] = c;
	fb[pos + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}

void fb_move_cursor(unsigned short pos) {
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	outb(FB_PORT_DATA, (unsigned char) ((pos >> 8) & 0x00ff));
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	outb(FB_PORT_DATA, (unsigned char) (pos & 0x00ff));
}

void fb_clear() {
	for (unsigned int i = 0; i < FB_MAX_POS; i++)
		fb_write_cell(i, ' ', FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);
	curr_pos = 0;
	fb_move_cursor(0);
}

void fb_copy_cell(unsigned int src, unsigned int dst) {
	src *= 2;
	dst *= 2;
	fb[dst] = fb[src];
	fb[dst + 1] = fb[src + 1];
}

void fb_scroll() {
	for (unsigned int i = FB_COLS; i < FB_MAX_POS; i++)
		fb_copy_cell(i, i - FB_COLS);
	for (unsigned int i = FB_MAX_POS - FB_COLS; i < FB_MAX_POS; i++)
		fb_write_cell(i, ' ', FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);
}

int fb_write(char *buf, unsigned int len) {
	unsigned int i = 0;
	for (i = 0; i < len; i++) {
		if (curr_pos >= FB_MAX_POS) {
			fb_scroll();
			curr_pos = FB_MAX_POS - FB_COLS;
		}
		fb_write_cell(curr_pos++, buf[i], FB_COLOR_BLACK, FB_COLOR_LIGHT_GREY);
		fb_move_cursor(curr_pos);
	}
	return (int) i;
}

void fb_puts(char *buf) {
	while (*buf)
		fb_write(buf++, 1);
}

void fb_putc(char c) {
	char *tmp = &c;
	fb_write(tmp, 1);
}