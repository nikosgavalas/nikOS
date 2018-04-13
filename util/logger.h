#ifndef _LOGGER_H_INCLUDED_
#define _LOGGER_H_INCLUDED_

typedef enum log_level {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	PANIC
} log_level_t;

typedef enum log_output {
	CONSOLE,
	COM1
} log_output_t;

void log(log_output_t dest, log_level_t lvl, char* msg);

#endif // _LOGGER_H_INCLUDED_