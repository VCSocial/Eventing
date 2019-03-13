#include "logger.h"

char * get_curr_time(void)
{
  char * buf = (char *) malloc(sizeof(char) * TIME_LEN);
  struct tm *now;
  time_t raw;
  time(&raw);
  now = localtime(&raw);

  if (strftime(buf, TIME_LEN, "%Y-%m-%d %H:%M:%S", now) == 0) {
    printf("STUB\n");
    // TODO Find better solution
    buf = "FAILURE\0";
  }
  return buf;
}

void info(const char * caller, const char * src, char * msg)
{
  char * time = get_curr_time();
  pid_t pid = getpid();

  printf(ANSI_GREEN "%s  INFO  %ld --- [%15s] %20s : %s\n" ANSI_RESET,
         time, (long) pid, caller, src, msg);
}

void warn(const char * caller, const char * src, char * msg)
{
  char * time = get_curr_time();
  pid_t pid = getpid();

  printf(ANSI_YELLOW "%s  WARN  %ld --- [%15s] %20s : %s\n" ANSI_RESET,
         time, (long) pid, caller, src, msg);
}

void erro(const char * caller, const char * src, char * msg)
{
  char * time = get_curr_time();
  pid_t pid = getpid();

  printf(ANSI_RED "%s  ERROR %ld --- [%15s] %20s : %s\n" ANSI_RESET,
         time, (long) pid, caller, src, msg);
}
