/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:11 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:22:12 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
#define ARGS_H

typedef struct s_args
{
	int number_of_coders;
	long time_to_burnout;
	long time_to_compile;
	long time_to_debug;
	long time_to_refactor;
	int number_of_compiles_required;
	long dongle_cooldown;
	int scheduler; // 0 = FIFO, 1 = EDF
}   t_args;

int     parse_args(int ac, char **av, t_args *args);
int     validate_args(t_args *args);
int     parse_scheduler(const char *str);

#endif
