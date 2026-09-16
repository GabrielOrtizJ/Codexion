/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:22:39 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 11:51:12 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_H
# define SCHEDULER_H

struct	s_coder;

typedef struct s_queue_node
{
	int		coder_id;
	long	priority;
}	t_queue_node;

typedef struct s_queue
{
	t_queue_node	*nodes;
	int				size;
	int				capacity;
}	t_queue;

void	queue_init(t_queue *q, int capacity);
void	queue_push(t_queue *q, int coder_id, long priority);
int		queue_pop(t_queue *q);
int		queue_is_empty(t_queue *q);
long	fifo_priority(void);
long	edf_priority(struct s_coder *c);

#endif
