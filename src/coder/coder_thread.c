#include "codexion.h"
#include "coder.h"
#include "dongle.h"
#include "log.h"

static void coder_loop(t_coder *c)
{
	t_simulation *sim = c->sim;
	t_dongle     *left;
	t_dongle     *right;
	int          stop;

	left = &sim->dongles[(c->id - 1) % sim->args.number_of_coders];
	right = &sim->dongles[c->id % sim->args.number_of_coders];
	if (sim->args.number_of_coders == 1)
		right = left;
	while (1)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		stop = sim->stop_simulation || c->compile_count >= sim->args.number_of_compiles_required;
		pthread_mutex_unlock(&sim->stop_mutex);
		if (stop)
			break;
		if (dongle_take(c, left) != 0)
			break;
		log_action(&sim->monitor.log, c->id, "has taken a dongle");
		if (sim->args.number_of_coders > 1)
		{
			if (dongle_take(c, right) != 0)
				break;
			log_action(&sim->monitor.log, c->id, "has taken a dongle");
		}
		coder_compile(c);
		coder_debug(c);
		coder_refactor(c);
		dongle_release(left);
		if (sim->args.number_of_coders > 1)
			dongle_release(right);
		c->compile_count++;
		if (c->compile_count >= sim->args.number_of_compiles_required)
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop_simulation = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			for (int i = 0; i < sim->args.number_of_coders; i++)
				pthread_cond_broadcast(&sim->dongles[i].cond);
			break;
		}
	}
}

void *coder_thread(void *ptr)
{
	t_coder *c = (t_coder *)ptr;

	coder_loop(c);
	return (NULL);
}
