/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:16 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:01:42 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init.h"
#include "coder.h"
#include "dongle.h"
#include "monitor.h"

void	destroy_simulation(t_simulation *sim)
{
	int i;

	if (sim == NULL)
		return ;
	pthread_mutex_destroy(&sim->stop_mutex);
	if (sim->coders != NULL)
	{
		i = 0;
		while (i < sim->args.number_of_coders)
		{
			pthread_mutex_destroy(&sim->coders[i].timestamp_mutex);
			i++;
		}
		free(sim->coders);
		sim->coders = NULL;
	}
	if (sim->dongles != NULL)
	{
		i = 0;
		while (i < sim->args.number_of_coders)
		{
			pthread_mutex_destroy(&sim->dongles[i].mutex);
			pthread_cond_destroy(&sim->dongles[i].cond);
			free(sim->dongles[i].queue.nodes);
			i++;
		}
		free(sim->dongles);
		sim->dongles = NULL;
	}
	pthread_mutex_destroy(&sim->monitor.log.mutex);
}
