#include "codexion.h"
#include "dongle.h"
#include "scheduler.h"

void dongle_queue_push(t_dongle *d, int coder_id, long priority)
{
	queue_push(&d->queue, coder_id, priority);
}

int dongle_queue_pop(t_dongle *d)
{
	return queue_pop(&d->queue);
}

int dongle_queue_peek(t_dongle *d)
{
	if (d->queue.size == 0)
		return -1;
	return d->queue.nodes[0].coder_id;
}
