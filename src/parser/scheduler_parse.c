#include "args.h"
#include <string.h>

int parse_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0)
		return 0;
	if (strcmp(str, "edf") == 0)
		return 1;
	return -1;
}
