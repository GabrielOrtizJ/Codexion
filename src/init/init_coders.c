/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:18 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/14 16:42:05 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init.h"
#include "coder.h"
#include "utils.h"

int init_coders(t_simulation *sim)
{
	int i;

	sim->coders = malloc(sizeof(t_coder) * sim->args.number_of_coders);
	if (!sim->coders)
		return (1);

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		t_coder *coder = &sim->coders[i];
		coder->id = i + 1;
		coder->compile_count = 0;
		coder->last_compile_start = time_ms();
		coder->sim = sim;
		pthread_mutex_init(&coder->timestamp_mutex, NULL);
		i++;
	}
	return (0);
}
