#ifndef LOG_H
#define LOG_H

#include <pthread.h>

typedef struct s_log
{
	pthread_mutex_t mutex;
	long            start_time;
}   t_log;

void    log_action(t_log *log, int coder_id, const char *msg);
long    timestamp_ms(void);

#endif
