/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:21 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:05:13 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init.h"
#include "dongle.h"
#include "scheduler.h"

int	init_dongles(t_simulation *sim)
{
	int			i;
	t_dongle	*d;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args.number_of_coders);
	if (!sim->dongles)
		return (1);
	i = 0;
	while (i < sim->args.number_of_coders)
	{
		d = &sim->dongles[i];
		pthread_mutex_init(&d->mutex, NULL);
		pthread_cond_init(&d->cond, NULL);
		d->last_release_time = 0;
		d->owner_id = -1;
		queue_init(&d->queue, sim->args.number_of_coders);
		i++;
	}
	return (0);
}
