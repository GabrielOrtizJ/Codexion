/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:29 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:23:30 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "utils.h"
#include <stdio.h>

void log_action(t_log *log, int coder_id, const char *msg)
{
	long ts;

	ts = time_ms() - log->start_time;
	pthread_mutex_lock(&log->mutex);
	printf("%ld %d %s\n", ts, coder_id, msg);
	fflush(stdout);
	pthread_mutex_unlock(&log->mutex);
}
