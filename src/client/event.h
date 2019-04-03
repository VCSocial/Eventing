#ifndef EVENT_H
#define EVENT_H

#define __USE_XOPEN 1
#define _GNU_SOURCE 1

/* Includes */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <syslog.h>

/* Macros */
#define assertf(msg, expr) assert(((void) (msg), (expr) ))

/* Constants */
#define MAX_EVENTS 256
#define UUID_LEN   37

struct event {
  char * uuid;
  unsigned int id;
  char * desc;
  time_t begin;
  double duration;
  time_t end;
};

/* Global Variables */
extern struct event *repository[MAX_EVENTS];
extern unsigned int auto_inc;

/* Functions */
unsigned int create_event(char desc[], char * begin, char * end);
time_t convert_to_unix_time(char * time_str);
void print_event(unsigned int id);
unsigned int delete_event(unsigned int id);

#endif /* END EVENT_H */
