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

int	is_var(char *s)
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
	t_env	*env;

	status = 0;
	while (arg_list)
	{
		arg = unname_argument(arg_list, env_list);
		if (!is_var(arg->name))
			status = ret_with_msg("unset: ", arg->name,
				": not a valid identifier", 1);
		if ((!ft_strcmp("PWD", arg->name) || !ft_strcmp("OLDPWD", arg->name) ||
		!ft_strcmp("CDPATH", arg->name)) && (env = get_env_by_key(arg->name,
			env_list, 1)))
			env->is_hidden = 2;
		else if (ft_strcmp("?", arg->name))
			ft_lst_elem_delete(&env_list
				, get_env_list_by_key(arg->name, env_list, 0), clear_env);
		arg_list = arg_list->next;
	}
	return (status);
}
