/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:32 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:33 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
** check for type == -1 made for default adding
** not default case: adding PWD and OLDPWD in cd, because in error we need free
*/

t_env	*add_env(t_list **env_list, char *key, char *value, int is_hidden)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->key = key;
	env->value = value;
	env->is_hidden = is_hidden;
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (env);
}

void	sort_envs(t_list *env_list)
{
	t_list	*begin;
	t_list	*begin2;
	void	*temp;

	begin = env_list;
	while (begin)
	{
		begin2 = env_list;
		while (begin2->next)
		{
			if (ft_strcmp(((t_env *)(begin2->content))->key,
				((t_env *)(begin2->next->content))->key) > 0)
			{
				temp = begin2->content;
				begin2->content = begin2->next->content;
				begin2->next->content = temp;
			}
			begin2 = begin2->next;
		}
		begin = begin->next;
	}
}

t_list	*envs_to_list(char *envp[])
{
	t_list	*env_list;
	char	*temp;

	env_list = NULL;
	while (*envp)
	{
		temp = to_delimiter(*envp, '=');
		add_env(&env_list, get_substr(*envp, temp),
			get_substr(temp ? temp + 1 : temp, NULL), 0);
		envp++;
	}
	add_env(&env_list, ft_strdup("?"), ft_strdup("0"), 1);
	if (!get_env_val_by_key("PWD", env_list))
		add_env(&env_list, ft_strdup("PWD"), getcwd(NULL, 228), 0);
	if (!get_env_val_by_key("OLDPWD", env_list))
		add_env(&env_list, ft_strdup("OLDPWD"), NULL, 2);
	sort_envs(env_list);
	return (env_list);
}

char	**env_list_to_array(t_list *env_list)
{
	int		i;
	int		j;
	char	**out;
	t_env	*env;

	i = ft_lstsize(env_list);
	if (!i || !(out = ft_calloc(sizeof(char *), i + 1)))
		return (NULL);
	j = -1;
	while (++j < i)
	{
		env = (t_env *)(env_list->content);
		str_append(&out[j], env->key);
		str_append(&out[j], "=");
		str_append(&out[j], env->value);
		env_list = env_list->next;
	}
	return (out);
}

void	print_env_array(char **envp)
{
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
}
