/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:45 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/25 17:07:46 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "log.h"
#include "utils.h"
#include <unistd.h>

static int	stop_requested(t_simulation *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop_simulation;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}

void	coder_compile(t_coder *c)
{
	t_simulation	*sim;

	sim = c->sim;
	if (stop_requested(sim))
		return ;
	pthread_mutex_lock(&c->timestamp_mutex);
	c->last_compile_start = time_ms();
	pthread_mutex_unlock(&c->timestamp_mutex);
	if (stop_requested(sim))
		return ;
	log_action(&sim->monitor.log, c->id, "is compiling");
	if (stop_requested(sim))
		return ;
	usleep(sim->args.time_to_compile * 1000);
}

void	coder_debug(t_coder *c)
{
	if (stop_requested(c->sim))
		return ;
	log_action(&c->sim->monitor.log, c->id, "is debugging");
	if (stop_requested(c->sim))
		return ;
	usleep(c->sim->args.time_to_debug * 1000);
}

void	coder_refactor(t_coder *c)
{
	if (stop_requested(c->sim))
		return ;
	log_action(&c->sim->monitor.log, c->id, "is refactoring");
	if (stop_requested(c->sim))
		return ;
	usleep(c->sim->args.time_to_refactor * 1000);
}
