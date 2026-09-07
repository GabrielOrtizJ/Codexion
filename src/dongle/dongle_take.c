#include "codexion.h"
#include "dongle.h"
#include "coder.h"
#include "scheduler.h"
#include "utils.h"
#include "log.h"

int dongle_take(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	while (1)
	{
		pthread_mutex_lock(&c->sim->stop_mutex);
		if (c->sim->stop_simulation)
		{
			pthread_mutex_unlock(&c->sim->stop_mutex);
			pthread_mutex_unlock(&d->mutex);
			return 1;
		}
		pthread_mutex_unlock(&c->sim->stop_mutex);
		if (timestamp_ms() - d->last_release_time >= c->sim->args.dongle_cooldown)
			break;
		pthread_cond_wait(&d->cond, &d->mutex);
	}

	long priority;
	if (c->sim->args.scheduler == 0)
		priority = fifo_priority();
	else
		priority = edf_priority(c);

	dongle_queue_push(d, c->id, priority);

	while (1)
	{
		pthread_mutex_lock(&c->sim->stop_mutex);
		if (c->sim->stop_simulation)
		{
			pthread_mutex_unlock(&c->sim->stop_mutex);
			pthread_mutex_unlock(&d->mutex);
			return 1;
		}
		pthread_mutex_unlock(&c->sim->stop_mutex);
		if (dongle_queue_peek(d) == c->id)
			break;
		pthread_cond_wait(&d->cond, &d->mutex);
	}

	dongle_queue_pop(d);
	pthread_mutex_unlock(&d->mutex);
	return 0;
}
