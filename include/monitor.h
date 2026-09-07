#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>
#include "log.h"

typedef struct s_monitor
{
    pthread_t thread;
    struct s_simulation *sim;
    t_log log;
}   t_monitor;

void    *monitor_thread(void *ptr);
int     check_burnout(t_monitor *m);

#endif
