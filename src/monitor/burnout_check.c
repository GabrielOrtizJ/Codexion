/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:53 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:23:54 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "codexion.h"
#include "log.h"
#include "utils.h"

int check_burnout(t_monitor *m)
{
	t_simulation *sim = m->sim;
	long now = timestamp_ms();

	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->stop_simulation)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		return 1;
	}
	pthread_mutex_unlock(&sim->stop_mutex);

	for (int i = 0; i < sim->args.number_of_coders; i++)
	{
		t_coder *c = &sim->coders[i];

		pthread_mutex_lock(&c->timestamp_mutex);
		long last = c->last_compile_start;
		pthread_mutex_unlock(&c->timestamp_mutex);

		if (now - last > sim->args.time_to_burnout)
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop_simulation = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			for (int j = 0; j < sim->args.number_of_coders; j++)
				pthread_cond_broadcast(&sim->dongles[j].cond);
			log_action(&m->log, c->id, "burned out");
			return 1;
		}
	}
	return 0;
}
