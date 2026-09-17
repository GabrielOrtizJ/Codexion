/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_take.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:13 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:00:59 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "dongle.h"
#include "coder.h"
#include "scheduler.h"
#include "utils.h"
#include "log.h"
#include <sys/time.h>
#include <unistd.h>

static int	stop_requested(t_simulation *sim)
{
	int			stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop_simulation;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}

static long	request_priority(t_coder *c)
{
	if (c->sim->args.scheduler == 0)
		return (fifo_priority());
	return (edf_priority(c));
}

static void	wait_for_dongle(t_dongle *d)
{
	struct timeval	now;
	struct timespec	deadline;

	gettimeofday(&now, NULL);
	deadline.tv_sec = now.tv_sec;
	deadline.tv_nsec = (now.tv_usec + 1000) * 1000;
	if (deadline.tv_nsec >= 1000000000)
	{
		deadline.tv_sec++;
		deadline.tv_nsec -= 1000000000;
	}
	pthread_cond_timedwait(&d->cond, &d->mutex, &deadline);
}

int	dongle_take(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	dongle_queue_push(d, c->id, request_priority(c));
	pthread_mutex_unlock(&d->mutex);
	while (1)
	{
		pthread_mutex_lock(&d->mutex);
		if (stop_requested(c->sim))
		{
			pthread_mutex_unlock(&d->mutex);
			return (1);
		}
		if (dongle_queue_peek(d) == c->id && d->owner_id == -1
			&& timestamp_ms() - d->last_release_time
			>= c->sim->args.dongle_cooldown)
		{
			dongle_queue_pop(d);
			d->owner_id = c->id;
			pthread_mutex_unlock(&d->mutex);
			return (0);
		}
		wait_for_dongle(d);
		pthread_mutex_unlock(&d->mutex);
	}
}
