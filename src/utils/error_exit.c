#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void error_exit(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}
