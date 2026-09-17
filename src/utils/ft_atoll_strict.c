/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_strict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:31 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:24:11 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

long	ft_atoll_strict(const char *str)
{
	long		result;
	int			i;

	result = 0;
	i = 0;
	if (!is_number(str))
		error_exit("Invalid number");
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			error_exit("Invalid number");
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
