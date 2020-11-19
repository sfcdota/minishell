#include "parser.h"

int		ft_strstr(const char *dest, const char *src)
{
	int		i;
	int		j;

	i = 0;
	if (*src == '\0' || !src)
		return (1);
	while (dest[i] != '\0')
	{
		j = 0;
		while (src[j] == dest[i + j])
		{
			if (src[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}