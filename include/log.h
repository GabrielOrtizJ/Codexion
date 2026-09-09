/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:35 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:22:36 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
#define LOG_H

#include <pthread.h>

typedef struct s_log
{
	pthread_mutex_t mutex;
	long            start_time;
}   t_log;

void    log_action(t_log *log, int coder_id, const char *msg);
long    timestamp_ms(void);

#endif
