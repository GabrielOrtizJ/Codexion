#include "utils.h"
#include <ctype.h>

int is_number(const char *str)
{
	int i = 0;

	if (!str || !*str)
		return 0;

	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return 0;
		i++;
	}
	return 1;
}
