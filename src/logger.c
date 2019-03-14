#include "logger.h"

char * get_curr_time(void)
{
  char * buf = (char *) malloc(sizeof(char) * TIME_LEN);
  struct tm *now;
  time_t raw;
  time(&raw);
  now = localtime(&raw);

  if (strftime(buf, TIME_LEN, "%Y-%m-%d %H:%M:%S", now) == 0) {
    buf = "FAILURE\0";
  }
  return buf;
}

void logger(const char * caller, const char * src, int lvl, const char * msg, ...)
{
  char * time = get_curr_time();
  pid_t pid = getpid();

  va_list arg;
  int done;

  printf("%s %s  %-5s %ld --- [%15s] %10s : ", color[lvl], time, type[lvl],
         (long) pid, caller, src);

  va_start (arg, msg);
  done = vfprintf (stdout, msg, arg);
  va_end (arg);

  printf(ANSI_RESET "\n");
}

