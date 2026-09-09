/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_timestamps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:23:01 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:23:02 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"

long coder_deadline(t_coder *c)
{
	long burnout = c->sim->args.time_to_burnout;
	return c->last_compile_start + burnout;
}
