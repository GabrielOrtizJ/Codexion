/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:58 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 13:05:10 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "dongle.h"
#include "log.h"

static int	take_two_dongles(t_coder *c, t_dongle *left, t_dongle *right)
{
	if (c->sim->args.number_of_coders < 2 || dongle_take(c, left) != 0)
		return (0);
	log_action(&c->sim->monitor.log, c->id, "has taken a dongle");
	if (dongle_take(c, right) != 0)
	{
		dongle_release(left);
		return (0);
	}
	log_action(&c->sim->monitor.log, c->id, "has taken a dongle");
	return (1);
}

static int	finish_compile(t_coder *c, t_dongle *left, t_dongle *right)
{
	t_simulation	*sim;

	sim = c->sim;
	pthread_mutex_lock(&sim->active_mutex);
	if (sim->active_compilers >= sim->args.number_of_coders / 2)
	{
		pthread_mutex_unlock(&sim->active_mutex);
		dongle_release(left);
		dongle_release(right);
		return (0);
	}
	sim->active_compilers++;
	pthread_mutex_unlock(&sim->active_mutex);
	coder_compile(c);
	dongle_release(left);
	dongle_release(right);
	pthread_mutex_lock(&sim->active_mutex);
	sim->active_compilers--;
	pthread_mutex_unlock(&sim->active_mutex);
	pthread_mutex_lock(&c->timestamp_mutex);
	c->compile_count++;
	pthread_mutex_unlock(&c->timestamp_mutex);
	coder_debug(c);
	coder_refactor(c);
	return (1);
}

static int	stop_threads(t_simulation *sim)
{
	int		i;

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
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop_simulation = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
	i = 0;
	while (i < sim->args.number_of_coders)
	{
		pthread_cond_broadcast(&sim->dongles[i].cond);
		i++;
	}
	return (1);
}

static void	coder_loop(t_coder *c)
{
	t_simulation	*sim;
	t_dongle		*left;
	t_dongle		*right;
	int				stop;
	int				i;

	sim = c->sim;
	left = &sim->dongles[(c->id - 1) % sim->args.number_of_coders];
	right = &sim->dongles[c->id % sim->args.number_of_coders];
	while (1)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		stop = sim->stop_simulation;
		pthread_mutex_unlock(&sim->stop_mutex);
		if (stop || stop_threads(sim))
			break ;
		if (take_two_dongles(c, left, right) == 0)
			continue ;
		if (finish_compile(c, left, right) == 0)
			continue ;
	}
}

void	*coder_thread(void *ptr)
{
	t_coder	*c;

	c = (t_coder *)ptr;
	coder_loop(c);
	return (NULL);
}
