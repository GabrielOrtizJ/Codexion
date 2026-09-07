#include "utils.h"
#include <stddef.h>
#include <sys/time.h>

long time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
