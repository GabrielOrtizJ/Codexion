#include "codexion.h"
#include "coder.h"

long coder_deadline(t_coder *c)
{
	long burnout = c->sim->args.time_to_burnout;
	return c->last_compile_start + burnout;
}
