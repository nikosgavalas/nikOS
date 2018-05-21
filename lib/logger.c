#include <logger.h>
#include <drivers/framebuffer.h>
#include <drivers/serial.h>

#include <stdarg.h> // C stdlib

void log_puts(log_output_t dest, char *level, char *msg)
{
	switch (dest) {
		case CONSOLE:
			fb_puts(level);
			fb_puts(msg);
			fb_puts("\n");
			break;
		case COM1:
			serial_puts(SERIAL_BASE_COM1, level);
			serial_puts(SERIAL_BASE_COM1, msg);
			serial_puts(SERIAL_BASE_COM1, "\n");
			break;
	}
}

void klog(log_output_t dest, log_level_t lvl, char *msg)
{
	switch (lvl) {
		case DEBUG:
			log_puts(dest, "[DEBUG] ", msg);
			break;
		case INFO:
			log_puts(dest, "[INFO] ", msg);
			break;
		case WARN:
			log_puts(dest, "[WARN] ", msg);
			break;
		case ERROR:
			log_puts(dest, "[ERROR] ", msg);
			break;
		case PANIC:
			log_puts(dest, "[PANIC] ", msg);
			break;
	}
}

/* void minitoa(int i)
{

} */

/* see K&R 2nd ed. */ 
void minprintf(char* format, ...) 
{
	va_list arg_ptr;
	char* p, c, s;
	int i;

	va_start(arg_ptr, format);
	
	for (*p = format; *p; p++) {
		if (*p != '%') {
			fb_putc(*p);
			continue;
		}
		switch (*++p) {
			case 'd':
				i = va_arg(arg_ptr, int);
				//fb_puts(minitoa(i));
				break;
			case 'c':
				c = va_arg(arg_ptr, char);
				fb_putc(c);
				break;
			case 's':
				s = va_arg(arg_ptr, char *);
				fb_puts(s);
				break;
			default:
				break;
		}
	}

	va_end(arg_ptr);
}
