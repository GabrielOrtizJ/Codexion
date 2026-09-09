/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:00 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:24:01 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "utils.h"
#include <stdio.h>

int parse_args(int ac, char **av, t_args *args)
{
	if (ac != 9)
	{
		fprintf(stderr, "Usage: codexion number_of_coders time_to_burnout "
						"time_to_compile time_to_debug time_to_refactor "
						"number_of_compiles_required dongle_cooldown scheduler\n");
		return (1);
	}
	args->number_of_coders = (int)ft_atoll_strict(av[1]);
	args->time_to_burnout = ft_atoll_strict(av[2]);
	args->time_to_compile = ft_atoll_strict(av[3]);
	args->time_to_debug = ft_atoll_strict(av[4]);
	args->time_to_refactor = ft_atoll_strict(av[5]);
	args->number_of_compiles_required = (int)ft_atoll_strict(av[6]);
	args->dongle_cooldown = ft_atoll_strict(av[7]);
	args->scheduler = parse_scheduler(av[8]);
	if (args->scheduler == -1)
	{
		fprintf(stderr, "Invalid scheduler: must be fifo or edf\n");
		return (1);
	}
	return (0);
}
