/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:34 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:24:35 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <ctype.h>

int is_number(const char *str)
{
	int i = 0;

	if (!str || !*str)
		return 0;

	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return 0;
		i++;
	}
	return 1;
}
