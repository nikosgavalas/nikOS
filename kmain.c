#define FB_BASE_ADDR 0x000B8000

#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

char *fb = (char *) FB_BASE_ADDR;

/* write to the framebuffer in location i, 
the given char c, with foreground color fg and 
background color bg */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}

void kmain()
{
	fb_write_cell(0, 'A', FB_BLACK, FB_LIGHT_GREY);
	return;
}

