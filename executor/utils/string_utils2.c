#include "executor.h"

/*
** Modifying str to lower register symbols
*/

void	uncapitalize_str(char *str)
{
	while (str && *str)
	{
		ft_tolower(*str);
		str++;
	}
}