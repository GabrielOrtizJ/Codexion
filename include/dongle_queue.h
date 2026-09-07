#ifndef DONGLE_QUEUE_H
#define DONGLE_QUEUE_H

struct s_dongle;

void dongle_queue_push(struct s_dongle *d, int coder_id, long priority);
int dongle_queue_pop(struct s_dongle *d);
int dongle_queue_peek(struct s_dongle *d);

#endif
