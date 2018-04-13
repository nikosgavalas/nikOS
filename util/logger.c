#include "logger.h"
#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"

void log_puts(log_output_t dest, char *level, char *msg) {
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

void log(log_output_t dest, log_level_t lvl, char *msg) {
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
