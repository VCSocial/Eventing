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
#include <stdarg.h>

/* Constants */
#define TIME_LEN 26
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_RESET   "\x1b[0m"
#define INFO         0
#define WARN         0
#define ERROR        0
#define LOG_TYPE_LEN 3

/* Global variables */
static char * type[LOG_TYPE_LEN]  = {"INFO", "WARN", "ERROR"};
static char * color[LOG_TYPE_LEN] = {ANSI_GREEN, ANSI_YELLOW, ANSI_RED};

/* Prototypes */
char * get_curr_time(void);
void logger(const char * caller, const char * src, int lvl, const char * msg, ...);

#endif /* END LOGGER_H */