#include "log.h"
#include "utils.h"
#include <stdio.h>

void log_action(t_log *log, int coder_id, const char *msg)
{
	long ts;

	ts = time_ms() - log->start_time;
	pthread_mutex_lock(&log->mutex);
	printf("%ld %d %s\n", ts, coder_id, msg);
	fflush(stdout);
	pthread_mutex_unlock(&log->mutex);
}
