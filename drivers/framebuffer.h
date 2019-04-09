#ifndef _FRAMEBUFFER_H_INCLUDED_
#define _FRAMEBUFFER_H_INCLUDED_

/* The framebuffer consists of 80 columns and 25 rows
 * of "cells" each of which is 2 bytes long
 */
#define FB_COLS 80
#define FB_ROWS 25
#define FB_MAX_POS 80 * 25

#define FB_COLOR_BLACK 0
#define FB_COLOR_BLUE 1
#define FB_COLOR_GREEN 2
#define FB_COLOR_CYAN 3
#define FB_COLOR_RED 4
#define FB_COLOR_MAGENTA 5
#define FB_COLOR_BROWN 6
#define FB_COLOR_LIGHT_GREY 7
#define FB_COLOR_DARK_GREY 8
#define FB_COLOR_LIGHT_BLUE 9
#define FB_COLOR_LIGHT_GREEN 10
#define FB_COLOR_LIGHT_CYAN 11
#define FB_COLOR_LIGHT_RED 12
#define FB_COLOR_LIGHT_MAGENTA 13
#define FB_COLOR_LIGHT_BROWN 14
#define FB_COLOR_WHITE 15

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);
void fb_clear();
void fb_scroll();
int fb_write(char *buf, unsigned int len);
void fb_puts(char *buf);
void fb_putc(char c);

#endif  // _FRAMEBUFFER_H_INCLUDED_
