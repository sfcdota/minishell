/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:29 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:30 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
** Gets environment variable value from environment list by key(dictionary-like)
*/

char	*get_env_val_by_key(char *key, t_list *env_list)
{
	t_env *env;

	while (key && env_list)
	{
		env = (t_env *)(env_list->content);
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env_list = env_list->next;
	}
	return (NULL);
}

/*
** Gets environment variable from environment list by key(dictionary-like)
*/

t_env	*get_env_by_key(char *key, t_list *env_list)
{
	t_env *env;

	while (env_list && key)
	{
		env = (t_env *)(env_list->content);
		if (!ft_strcmp(key, env->key))
			return (env);
		env_list = env_list->next;
	}
	return (NULL);
}

/*
** Gets list that contain environment variable
** from environment list by key(dictionary-like)
*/

t_list	*get_env_list_by_key(char *key, t_list *env_list)
{
	while (env_list)
	{
		if (!ft_strcmp(key, ((t_env *)(env_list->content))->key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
