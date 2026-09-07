#ifndef DONGLE_H
#define DONGLE_H

#include <pthread.h>
#include "scheduler.h"
#include "coder.h"

typedef struct s_dongle
{
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	long            last_release_time;
	t_queue         queue;
}   t_dongle;

int     dongle_take(t_coder *c, t_dongle *d);
void    dongle_release(t_dongle *d);

#endif
