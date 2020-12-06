/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:42 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:43 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if ((!s1 && !s2))
		return (0);
	while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*to_delimiter(char *envp_string, char delimiter)
{
	while (*envp_string && *envp_string != delimiter)
		envp_string++;
	return (envp_string);
}

char	*get_substr(char *begin, char *end)
{
	char *out;

	if (!end)
		end = to_delimiter(begin, '\0');
	if (!begin || !*begin || !(out = ft_calloc(sizeof(char), end - begin + 2)))
		return (NULL);
	ft_strlcpy(out, begin, end - begin + 1);
	return (out);
}

char	*str_append(char **s1, char *s2)
{
	char *temp;

	temp = ft_strjoin(*s1, s2);
	clear_ptr((void **)s1);
	*s1 = temp;
}

char	*str_replace(char *s1, char *s2)
{
	clear_ptr((void **)&s1);
	s1 = ft_strdup(s2);
	clear_ptr((void **)&s2);
	return (s1);
}
