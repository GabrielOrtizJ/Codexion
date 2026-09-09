/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:02 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:24:03 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include <string.h>

int parse_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0)
		return 0;
	if (strcmp(str, "edf") == 0)
		return 1;
	return -1;
}
