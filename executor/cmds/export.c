/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:01:05 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:01:06 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Prints all environment variables (excluding hidden as well as $?)
** prefix - for unifying func for both export and env command
*/

void	print_env_list(t_list *env_list, char *prefix, int std_out)
{
	t_env *env;

	while (env_list)
	{
		if (!(env = (t_env *)(env_list->content))->is_hidden)
		{
			if (prefix)
				ft_putstr_fd(prefix, std_out);
			ft_putstr_fd(env->key, std_out);
			if (env->value)
			{
				ft_putchar_fd('=', std_out);
				if (prefix)
					ft_putchar_fd('\"', std_out);
				ft_putstr_fd(env->value, std_out);
				if (prefix)
					ft_putchar_fd('\"', std_out);
			}
			ft_putchar_fd('\n', std_out);
		}
		env_list = env_list->next;
	}
}

/*
** Check if var has valid name
*/

int		is_correct_var(char *s)
{
	if (!s)
		return (0);
	if (ft_isdigit(*s) || *s == '=')
		return (0);
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

/*
** Export execution
*/

int		export(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	t_arg	*arg;
	char	*tmp;
	int		status;

	status = 0;
	if (!arg_list)
		print_env_list(env_list, "declare -x ", cmd->out);
	while (arg_list)
	{
		arg = unname_argument(arg_list, env_list);
		tmp = to_delimiter(arg->name, '=');
		if (!is_correct_var(arg->name))
		{
			status = ret_with_msg("export: ", arg->name,
				": not a valid identifier", 1);
			arg_list = arg_list->next;
			continue;
		}
		export_env(arg, tmp, env_list);
		arg_list = arg_list->next;
	}
	return (status);
}
