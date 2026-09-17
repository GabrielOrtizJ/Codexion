/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:37 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 11:49:44 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include <pthread.h>
# include "log.h"

typedef struct s_monitor
{
	pthread_t			thread;
	struct s_simulation	*sim;
	t_log				log;
}	t_monitor;

void	*monitor_thread(void *ptr);
int		check_burnout(t_monitor *m);

#endif
