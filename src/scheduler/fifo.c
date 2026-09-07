#include "scheduler.h"
#include "utils.h"

long fifo_priority(void)
{
	return timestamp_ms();
}
