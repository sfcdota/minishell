/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:42:37 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:48:13 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_env(int *i, char *arg, t_list *env_list)
{
	char	*env_name;
	int		j;

	j = *i;
	env_name = (char *)malloc(sizeof(char) * 1);
	env_name[0] = '\0';
	while (!own_strchr("$' =\\\"", arg[j]) && arg[j])
	{
		if (arg[j] == '/')
			while (arg[j] == '/')
				j++;
		else
			env_name = strj(env_name, arg[j++]);
	}
	*i = --j;
	if (!env_name[0])
	{
		free(env_name);
		return (ft_strdup(""));
	}
	return (get_env_value_by_key(env_name, env_list, 0));
}

char *get_env_value_by_key(char *key, t_list *env_list, int supermode)
{
	t_env	*env;

	while (key && env_list)
	{
		env = (t_env *)(env_list->content);
		if (!own_strcmp(key, env->key) && (env->is_hidden != 2 || supermode))
			return (env->value);
		env_list = env_list->next;
	}
	return ("");
}

int		own_strcmp(const char *s1, const char *s2)
{
	if ((!s1[0] || !s2[0]))
		return (0);
	while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int		own_strchr(char *str, char ch)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == ch)
			return (1);
	return (0);
}

char	*strj(char *s1, char s2)
{
	unsigned int	i;
	char			*out_str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	if (!(out_str = malloc(sizeof(char) * (ft_strlen(s1) + 2))))
		return (NULL);
	while (s1[++i])
		out_str[i] = s1[i];
	free(s1);
	out_str[i++] = s2;
	out_str[i] = '\0';
	return (out_str);
}
