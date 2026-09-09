/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:45 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:22:46 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "log.h"
#include "utils.h"
#include <unistd.h>

void coder_compile(t_coder *c)
{
	t_simulation *sim = c->sim;

	pthread_mutex_lock(&c->timestamp_mutex);
	c->last_compile_start = time_ms();
	pthread_mutex_unlock(&c->timestamp_mutex);

	log_action(&sim->monitor.log, c->id, "is compiling");
	usleep(sim->args.time_to_compile * 1000);

	c->compile_count++;
}

void coder_debug(t_coder *c)
{
	log_action(&c->sim->monitor.log, c->id, "is debugging");
	usleep(c->sim->args.time_to_debug * 1000);
}

void coder_refactor(t_coder *c)
{
	log_action(&c->sim->monitor.log, c->id, "is refactoring");
	usleep(c->sim->args.time_to_refactor * 1000);
}
