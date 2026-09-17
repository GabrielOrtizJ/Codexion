/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:24:15 by gortiz-j          #+#    #+#             */
/*   Updated: 2026/09/16 12:55:26 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"
#include <stdlib.h>

static int	node_before(t_queue_node *first, t_queue_node *second)
{
	if (first->priority != second->priority)
		return (first->priority < second->priority);
	return (first->order < second->order);
}

void	queue_init(t_queue *q, int capacity)
{
	q->nodes = (t_queue_node *)malloc(sizeof(t_queue_node) * capacity);
	q->size = 0;
	q->capacity = capacity;
	q->next_order = 0;
}

void	queue_push(t_queue *q, int coder_id, long priority)
{
	int				idx;
	int				parent;
	t_queue_node	tmp;

	if (q->size >= q->capacity)
		return ;
	q->nodes[q->size].coder_id = coder_id;
	q->nodes[q->size].priority = priority;
	q->nodes[q->size].order = q->next_order++;
	idx = q->size;
	q->size++;
	while (idx > 0)
	{
		parent = (idx - 1) / 2;
		if (!node_before(&q->nodes[idx], &q->nodes[parent]))
			break ;
		tmp = q->nodes[idx];
		q->nodes[idx] = q->nodes[parent];
		q->nodes[parent] = tmp;
		idx = parent;
	}
}

static void	heapify_down(t_queue *q, int idx)
{
	int				left;
	int				right;
	int				smallest;
	t_queue_node	tmp;

	while (1)
	{
		left = 2 * idx + 1;
		right = 2 * idx + 2;
		smallest = idx;
		if (left < q->size)
			if (node_before(&q->nodes[left], &q->nodes[smallest]))
				smallest = left;
		if (right < q->size)
			if (node_before(&q->nodes[right], &q->nodes[smallest]))
				smallest = right;
		if (smallest == idx)
			break ;
		tmp = q->nodes[idx];
		q->nodes[idx] = q->nodes[smallest];
		q->nodes[smallest] = tmp;
		idx = smallest;
	}
}

int	queue_pop(t_queue *q)
{
	int				coder_id;

	if (q->size == 0)
		return (-1);
	coder_id = q->nodes[0].coder_id;
	q->nodes[0] = q->nodes[q->size - 1];
	q->size--;
	heapify_down(q, 0);
	return (coder_id);
}
