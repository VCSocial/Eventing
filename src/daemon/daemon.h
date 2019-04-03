#ifndef DAEMON_H
#define DAEMON_H

#define __USE_XOPEN 1
#define _GNU_SOURCE 1
#define _DEFAULT_SOURCE

/* Includes */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>

/* Constants */
#define MAX_EVENTS 256
#define LOG_STDOUT(...) vfprintf (__VA_ARGS__)

/* Global Variables */
extern struct event *repository[MAX_EVENTS];
extern unsigned int auto_inc;

#endif /* END DAEMON_H */
