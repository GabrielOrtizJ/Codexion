/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:30 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/25 17:02:47 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include <pthread.h>
# include "scheduler.h"
# include "coder.h"

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long			last_release_time;
	int				owner_id;
	t_queue			queue;
}	t_dongle;

int		dongle_take(t_coder *c, t_dongle *d);
void	dongle_release(t_dongle *d);

void	dongle_queue_push(struct s_dongle *d, int coder_id, long priority);
int		dongle_queue_pop(struct s_dongle *d);
int		dongle_queue_peek(struct s_dongle *d);

#endif
