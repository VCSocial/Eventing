#ifndef LOGGER_H
#define LOGGER_H

#define __USE_XOPEN 1
#define _GNU_SOURCE 1

/* Includes */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* Constants */
#define TIME_LEN 26
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_RESET   "\x1b[0m"

char * get_curr_time(void);
void info(const char * caller, const char * src, char * msg);
void warn(const char * caller, const char * src, char * msg);
void erro(const char * caller, const char * src, char * msg);

#endif /* END LOGGER_H */
