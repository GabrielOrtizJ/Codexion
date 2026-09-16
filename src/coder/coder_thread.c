/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:58 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 11:58:30 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "dongle.h"
#include "log.h"

static int	all_coders_reached_target(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].timestamp_mutex);
		if (sim->coders[i].compile_count
			< sim->args.number_of_compiles_required)
		{
			pthread_mutex_unlock(&sim->coders[i].timestamp_mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->coders[i].timestamp_mutex);
		i++;
	}
	return (1);
}

static void	coder_loop(t_coder *c)
{
	t_simulation	*sim = c->sim;
	t_dongle		*left;
	t_dongle		*right;
	int				stop;
	int				pair_index;

	if (sim->args.number_of_coders < 2)
		return ;
	if (sim->args.number_of_coders % 2 == 0)
	{
		pair_index = (c->id - 1) % (sim->args.number_of_coders / 2);
		left = &sim->dongles[pair_index * 2];
		right = &sim->dongles[pair_index * 2 + 1];
	}
	else
	{
		left = &sim->dongles[(c->id - 1) % sim->args.number_of_coders];
		right = &sim->dongles[c->id % sim->args.number_of_coders];
	}
	while (1)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		stop = sim->stop_simulation;
		pthread_mutex_unlock(&sim->stop_mutex);
		if (stop)
			break ;
		if (dongle_take(c, left) != 0)
			continue ;
		log_action(&sim->monitor.log, c->id, "has taken a dongle");
		if (sim->args.number_of_coders > 1)
		{
			if (dongle_take(c, right) != 0)
			{
				dongle_release(left);
				continue ;
			}
			log_action(&sim->monitor.log, c->id, "has taken a dongle");
		}
		pthread_mutex_lock(&sim->active_mutex);
		if (sim->active_compilers >= sim->args.number_of_coders / 2)
		{
			pthread_mutex_unlock(&sim->active_mutex);
			dongle_release(left);
			if (sim->args.number_of_coders > 1)
				dongle_release(right);
			continue ;
		}
		sim->active_compilers++;
		pthread_mutex_unlock(&sim->active_mutex);
		coder_compile(c);
		dongle_release(left);
		if (sim->args.number_of_coders > 1)
			dongle_release(right);
		pthread_mutex_lock(&sim->active_mutex);
		sim->active_compilers--;
		pthread_mutex_unlock(&sim->active_mutex);
		pthread_mutex_lock(&c->timestamp_mutex);
		c->compile_count++;
		pthread_mutex_unlock(&c->timestamp_mutex);
		coder_debug(c);
		coder_refactor(c);
		pthread_mutex_lock(&sim->stop_mutex);
		stop = sim->stop_simulation || all_coders_reached_target(sim);
		pthread_mutex_unlock(&sim->stop_mutex);
		if (stop)
		{
			if (all_coders_reached_target(sim))
			{
				pthread_mutex_lock(&sim->stop_mutex);
				sim->stop_simulation = 1;
				pthread_mutex_unlock(&sim->stop_mutex);
				for (int i = 0; i < sim->args.number_of_coders; i++)
					pthread_cond_broadcast(&sim->dongles[i].cond);
			}
			break ;
		}
	}
}

void *coder_thread(void *ptr)
{
	t_coder	*c = (t_coder *)ptr;
	c = (t_coder *)ptr;
	coder_loop(c);
	return (NULL);
}
