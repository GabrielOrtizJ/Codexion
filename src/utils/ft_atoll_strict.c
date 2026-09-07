#include "utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

long ft_atoll_strict(const char *str)
{
	long result = 0;
	int i = 0;

	if (!str || !*str)
		error_exit("Invalid number");

	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			error_exit("Invalid number");
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}
