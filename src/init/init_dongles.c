#include "codexion.h"
#include "init.h"
#include "dongle.h"
#include "scheduler.h"

int init_dongles(t_simulation *sim)
{
	int i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args.number_of_coders);
	if (!sim->dongles)
		return (1);

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		t_dongle *d = &sim->dongles[i];
		pthread_mutex_init(&d->mutex, NULL);
		pthread_cond_init(&d->cond, NULL);
		d->last_release_time = 0;
		queue_init(&d->queue, sim->args.number_of_coders);
		i++;
	}
	return (0);
}
