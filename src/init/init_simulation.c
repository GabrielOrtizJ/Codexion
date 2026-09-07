#include "codexion.h"
#include "init.h"
#include "coder.h"
#include "dongle.h"
#include "monitor.h"


int init_simulation(t_simulation *sim, t_args *args)
{
	sim->args = *args;
	sim->stop_simulation = 0;

	pthread_mutex_init(&sim->stop_mutex, NULL);

	if (init_coders(sim) != 0)
		return (1);
	if (init_dongles(sim) != 0)
		return (1);
	if (init_monitor(sim) != 0)
		return (1);

	return (0);
}
