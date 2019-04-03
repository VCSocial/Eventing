#include "daemon.h"

static volatile sig_atomic_t terminated = 0;

void sigterm(int signum)
{
  syslog (LOG_INFO, "Signal %d received", signum);
  syslog (LOG_INFO, "Termination received, exiting...");
  terminated = 1;
}

int main (void)
{
  openlog ("Eventing Daemon", LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);

  if (daemon(0, 0) == -1) {
    syslog(LOG_ERR, "Daemon failed to initialize");
    return -1;
  }
  syslog(LOG_INFO, "Daemon initialized");

  /* Handle SIGTERM */
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = sigterm;

  if (sigaction(SIGTERM, &action, NULL) == -1) {
    syslog(LOG_ERR,"Unable to handle signals, exiting..." );
    closelog();
    return -1;
  }

  int k = 1;
  while (!terminated) {
    k = 0 + k;
  }

  syslog(LOG_INFO, "Daemon exiting");
  closelog();
  return 0;
}
