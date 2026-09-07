#include "scheduler.h"
#include <stdlib.h>

static void swap_nodes(t_queue_node *a, t_queue_node *b)
{
	t_queue_node tmp = *a;
	*a = *b;
	*b = tmp;
}

void queue_init(t_queue *q, int capacity)
{
	q->nodes = (t_queue_node *)malloc(sizeof(t_queue_node) * capacity);
	q->size = 0;
	q->capacity = capacity;
}

static void heapify_up(t_queue *q, int idx)
{
	while (idx > 0)
	{
		int parent = (idx - 1) / 2;
		if (q->nodes[idx].priority >= q->nodes[parent].priority)
			break;
		swap_nodes(&q->nodes[idx], &q->nodes[parent]);
		idx = parent;
	}
}

void queue_push(t_queue *q, int coder_id, long priority)
{
	if (q->size >= q->capacity)
		return;
	q->nodes[q->size].coder_id = coder_id;
	q->nodes[q->size].priority = priority;
	heapify_up(q, q->size);
	q->size++;
}

static void heapify_down(t_queue *q, int idx)
{
	while (1)
	{
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		int smallest = idx;

		if (left < q->size && q->nodes[left].priority < q->nodes[smallest].priority)
			smallest = left;
		if (right < q->size && q->nodes[right].priority < q->nodes[smallest].priority)
			smallest = right;
		if (smallest == idx)
			break;
		swap_nodes(&q->nodes[idx], &q->nodes[smallest]);
		idx = smallest;
	}
}

int queue_pop(t_queue *q)
{
	int coder_id;

	if (q->size == 0)
		return (-1);
	coder_id = q->nodes[0].coder_id;
	q->nodes[0] = q->nodes[q->size - 1];
	q->size--;
	heapify_down(q, 0);
	return (coder_id);
}

int queue_is_empty(t_queue *q)
{
	return (q->size == 0);
}
