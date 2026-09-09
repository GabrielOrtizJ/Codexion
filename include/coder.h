/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:23 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/09 12:22:24 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
#define CODER_H

#include <pthread.h>

typedef struct s_coder
{
	int             id;
	int             compile_count;
	long            last_compile_start;
	pthread_t       thread;
	pthread_mutex_t timestamp_mutex;
	struct s_simulation *sim;
}   t_coder;

void    *coder_thread(void *ptr);
void    coder_compile(t_coder *c);
void    coder_debug(t_coder *c);
void    coder_refactor(t_coder *c);
long    coder_deadline(t_coder *c);

#endif
