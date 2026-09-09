/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:32 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:23:33 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include <stddef.h>
#include <sys/time.h>

long timestamp_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
