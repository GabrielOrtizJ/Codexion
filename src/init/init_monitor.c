#include "codexion.h"
#include "init.h"
#include "monitor.h"
#include "log.h"

int init_monitor(t_simulation *sim)
{
	sim->monitor.sim = sim;
	sim->monitor.log.start_time = time_ms();
	pthread_mutex_init(&sim->monitor.log.mutex, NULL);
	return (0);
}
