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

/*
** Original strcmp function
*/

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

/*
** Returns pointer to delimiter symbol in envp_string, if it's not exist, point
** to NULL
*/

char	*to_delimiter(char *envp_string, char delimiter)
{
	while (*envp_string && *envp_string != delimiter)
		envp_string++;
	return (envp_string);
}

/*
** Gets substring by begin and end pointer which must be pointers of an existing
** array of chars(string)
** If end equals to NULL - gets substring from begin to '\0'
** If begin equals to NULL - returns NULL
*/

char	*get_substr(char *begin, char *end)
{
	char *out;

	if (!end)
		end = to_delimiter(begin, '\0');
	if (!begin || !*begin || !(out = ft_calloc(sizeof(char), end - begin + 1)))
		return (NULL);
	ft_strlcpy(out, begin, end - begin + 1);
	return (out);
}

/*
** Concats two strings into the first argument with memory free of only 
** an old value
*/

char	*str_append(char **s1, char *s2)
{
	char *temp;

	temp = ft_strjoin(*s1, s2);
	clear_ptr((void **)s1);
	*s1 = temp;
	return (*s1);
}

/*
** Replace 1st argument by 2nd like strdup, but with memory free of an old value
** And returns 1st argument (pointer to begin of char array)
*/

char	*str_replace(char **s1, char *s2)
{
	if (!ft_strcmp(*s1, s2))
	{
		clear_ptr((void **)&s2);
		return (*s1);
	}
	clear_ptr((void **)s1);
	*s1 = s2;	
	return (*s1);
}
