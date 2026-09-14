/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_take.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:13 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/14 11:52:59 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "dongle.h"
#include "coder.h"
#include "scheduler.h"
#include "utils.h"
#include "log.h"
#include <time.h>

int dongle_take(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	pthread_mutex_lock(&c->sim->stop_mutex);
	if (c->sim->stop_simulation)
	{
		pthread_mutex_unlock(&c->sim->stop_mutex);
		pthread_mutex_unlock(&d->mutex);
		return 1;
	}
	pthread_mutex_unlock(&c->sim->stop_mutex);
	if (d->owner_id != -1)
	{
		pthread_mutex_unlock(&d->mutex);
		return 1;
	}
	if (timestamp_ms() - d->last_release_time < c->sim->args.dongle_cooldown)
	{
		pthread_mutex_unlock(&d->mutex);
		return 1;
	}
	d->owner_id = c->id;
	pthread_mutex_unlock(&d->mutex);
	return 0;
}
