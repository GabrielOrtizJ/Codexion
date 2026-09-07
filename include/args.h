#ifndef ARGS_H
#define ARGS_H

typedef struct s_args
{
	int number_of_coders;
	long time_to_burnout;
	long time_to_compile;
	long time_to_debug;
	long time_to_refactor;
	int number_of_compiles_required;
	long dongle_cooldown;
	int scheduler; // 0 = FIFO, 1 = EDF
}   t_args;

int     parse_args(int ac, char **av, t_args *args);
int     validate_args(t_args *args);
int     parse_scheduler(const char *str);

#endif
