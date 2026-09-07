#include "codexion.h"
#include "monitor.h"
#include "log.h"

void *monitor_thread(void *ptr)
{
	t_monitor *m = (t_monitor *)ptr;
	t_simulation *sim = m->sim;

	while (1)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop_simulation)
		{
			pthread_mutex_unlock(&sim->stop_mutex);
			break;
		}
		pthread_mutex_unlock(&sim->stop_mutex);
		if (check_burnout(m))
			break;
		usleep(1000);
	}
	return (NULL);
}
