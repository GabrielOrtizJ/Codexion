/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:05 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 11:46:00 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# include "args.h"
# include "utils.h"
# include "log.h"
# include "scheduler.h"
# include "dongle_queue.h"
# include "coder.h"
# include "dongle.h"
# include "monitor.h"
# include "init.h"

typedef struct s_simulation
{
	t_args			args;
	t_coder			*coders;
	t_dongle		*dongles;
	t_monitor		monitor;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
}	t_simulation;

#endif
