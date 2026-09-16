/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:50 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:30:33 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	create_monitor_thread(t_simulation *sim)
{
	if (pthread_create(&sim->monitor.thread, NULL, monitor_thread,
			&sim->monitor) != 0)
	{
		fprintf(stderr, "monitor thread creation failed\n");
		destroy_simulation(sim);
		return (1);
	}
	return (0);
}

static int	create_coder_threads(t_simulation *sim)
{
	int		i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL, coder_thread,
				&sim->coders[i]) != 0)
		{
			fprintf(stderr, "coder thread creation failed\n");
			destroy_simulation(sim);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_coder_threads(t_simulation *sim)
{
	int		i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_args			args;
	t_simulation	sim;

	if (parse_args(ac, av, &args) != 0 || validate_args(&args) != 0)
		return (1);
	if (init_simulation(&sim, &args) != 0)
		return (1);
	if (create_monitor_thread(&sim) != 0)
		return (1);
	if (create_coder_threads(&sim) != 0)
		return (1);
	join_coder_threads(&sim);
	pthread_join(sim.monitor.thread, NULL);
	destroy_simulation(&sim);
	return (0);
}
