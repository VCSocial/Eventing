#include "logger.h"

/* Variables */
static char * type[LOG_TYPE_LEN] = {"INFO", "WARN", "ERROR"};
static char * color[LOG_TYPE_LEN] = {ANSI_GREEN, ANSI_YELLOW, ANSI_RED};

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
  if ((done = vfprintf (stdout, msg, arg)) < 0) {
    printf("%s Failure to parse logged message", color[lvl]);
  }
  va_end (arg);

  printf(ANSI_RESET "\n");
}

