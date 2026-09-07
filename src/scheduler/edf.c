#include "scheduler.h"
#include "coder.h"

long edf_priority(t_coder *c)
{
	return coder_deadline(c);
}
