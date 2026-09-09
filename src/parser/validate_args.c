/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:05 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:24:06 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include <stdio.h>

int validate_args(t_args *a)
{
	if (a->number_of_coders <= 0
		|| a->time_to_burnout <= 0
		|| a->time_to_compile <= 0
		|| a->time_to_debug < 0
		|| a->time_to_refactor < 0
		|| a->number_of_compiles_required <= 0
		|| a->dongle_cooldown < 0)
	{
		fprintf(stderr, "Invalid arguments: must be positive integers\n");
		return (1);
	}
	return (0);
}
