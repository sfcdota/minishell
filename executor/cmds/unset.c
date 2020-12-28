/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:01:10 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:01:11 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int		is_var(char *s)
{
	if (!s)
		return (0);
	if (ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

/*
** Unset execution
*/

int	unset(t_list *arg_list, t_list *env_list)
{
	t_arg	*arg;
	int		status;

	status = 0;
	while (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		str_replace(&arg->name, pure_d(arg->name, &g_info));
		str_replace(&arg->name, execute_d(arg->name, env_list));
		if (!is_var(arg->name))
			status = ret_with_msg("unset: ", arg->name,
				": not a valid identifier", 1);
		if (!ft_strcmp("PWD", arg->name) || !ft_strcmp("OLDPWD", arg->name) ||
		!ft_strcmp("CDPATH", arg->name))
			get_env_by_key(arg->name, env_list)->is_hidden = 1;
		if (ft_strcmp("?", arg->name))
			ft_lst_elem_delete(&env_list
				, get_env_list_by_key(arg->name, env_list), clear_env);
		arg_list = arg_list->next;
	}
	return (status);
}
