/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:53 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:56:03 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "codexion.h"
#include "log.h"
#include "utils.h"

static void	broadcast_dongles(t_simulation *sim)
{
	int		i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		pthread_cond_broadcast(&sim->dongles[i].cond);
		i++;
	}
}

static int	coder_is_burned_out(t_coder *c, long now, t_simulation *sim)
{
	long		last;

	pthread_mutex_lock(&c->timestamp_mutex);
	last = c->last_compile_start;
	pthread_mutex_unlock(&c->timestamp_mutex);
	return (now - last > sim->args.time_to_burnout);
}

static int	stop_requested(t_simulation *sim)
{
	int		stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop_simulation;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}

int	check_burnout(t_monitor *m)
{
	t_simulation	*sim;
	t_coder			*c;
	long			now;
	int				i;

	sim = m->sim;
	now = timestamp_ms();
	if (stop_requested(sim))
		return (1);
	i = 0;
	while (i < sim->args.number_of_coders)
	{
		c = &sim->coders[i];
		if (coder_is_burned_out(c, now, sim))
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop_simulation = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			broadcast_dongles(sim);
			log_action(&m->log, c->id, "burned out");
			return (1);
		}
		i++;
	}
	return (0);
}
