#include "event.h"

unsigned int create_event(char desc[], char * begin, char * end) 
{
    struct event *new_event = (struct event *)
        malloc(sizeof(struct event));
    
    new_event->id = auto_inc;
    new_event->desc = strdup(desc);
    new_event->begin = convert_to_unix_time(begin);
    new_event->end   = convert_to_unix_time(end);
    new_event->duration = difftime(new_event->end, new_event->begin);

    repository[auto_inc++] = new_event; 

    if (repository[new_event->id] == NULL  || repository[new_event->id == 0]) {
      return 0;
    }

    return new_event->id; // Return the id of the stored event
}

time_t convert_to_unix_time(char * time_str) 
{
    struct tm tm;
    struct tm *now;

    time_t timestamp = (time_t) -1;
    time_t raw = (time_t) -1;
    
    time(&raw); 
    now = localtime(&raw);

    if ( strptime(time_str, "%H:%M", &tm) != NULL) {
        tm.tm_mon  = now->tm_mon; 
        tm.tm_year = now->tm_year; 
        tm.tm_mday = now->tm_mday; 

        timestamp = mktime(&tm);
    }
    assertf("[EVENT:convert_to_unix_time] failed to convert!", 
            timestamp > 0);

    return timestamp;
}

void print_event(unsigned int id) 
{
   struct event *requested = repository[id]; 
   printf("===============================================================\n");
   printf("| %-11s | %d\n", "ID", id);
   printf("| %-10s | %s\n", "Description", requested->desc);
   printf("| %-11s | %s", "Begin Time", ctime(&requested->begin));
   printf("| %-11s | %f\n", "Duration",  requested->duration);
   printf("| %-11s | %s", "End Time", ctime(&requested->end));
   printf("===============================================================\n");
}
