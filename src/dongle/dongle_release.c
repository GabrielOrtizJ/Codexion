#include "codexion.h"
#include "dongle.h"
#include "utils.h"

void dongle_release(t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->last_release_time = timestamp_ms();
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}
