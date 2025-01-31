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

#include "../executor.h"

/*
** Adds new environment variable (t_env) to environment list with param values
*/

t_env	*add_env(t_list **env_list, char *key, char *value, int is_hidden)
{
	t_env *env;

	if (!(env = ft_calloc(1, sizeof(t_env))))
		return (NULL);
	env->key = key;
	env->value = value;
	env->is_hidden = is_hidden;
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (env);
}

/*
** Sorts environment list by ascending the values of its content key(char *)
*/

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

/*
** Cast char *[] environment array to list(t_list)
*/

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
	add_env(&env_list, ft_strdup("~"), ft_strdup(get_env_val_by_key("HOME",
		env_list, 0)), 1);
	if (!get_env_val_by_key("PWD", env_list, 1))
		add_env(&env_list, ft_strdup("PWD"), getcwd(NULL, 228), 0);
	if (!get_env_val_by_key("OLDPWD", env_list, 1))
		add_env(&env_list, ft_strdup("OLDPWD"), NULL, 2);
	sort_envs(env_list);
	return (env_list);
}

/*
** Cast environment list to an char **array
*/

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
	out[i] = NULL;
	return (out);
}

/*
** Prints char** envp array
*/

void	export_env(char *delimiter_ptr, char *tmp, t_list *env_list)
{
	char	*temp_arg;
	t_env	*env;

	if ((temp_arg = get_substr(delimiter_ptr, tmp)) && *temp_arg)
	{
		if ((env = get_env_by_key(temp_arg, env_list, 1)))
		{
			str_replace(&temp_arg, get_substr(tmp ? tmp + 1 : tmp, NULL));
			if (ft_strcmp(env->value, temp_arg))
				str_replace(&env->value, temp_arg);
		}
		else
			add_env(&env_list, temp_arg, tmp && *tmp ?
			get_substr(tmp + 1, NULL) : NULL, 0);
	}
	else
		clear_ptr((void **)&temp_arg);
}
