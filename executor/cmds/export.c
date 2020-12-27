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
	t_arg *arg;
	char *temp;
	char *temp_arg;
	t_env *env;

	if (!arg_list)
		print_env_list(env_list, "declare -x ", cmd->out);
	while (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		str_replace(&arg->name, pure_$(arg->name, &g_info));
		str_replace(&arg->name, execute_$(arg->name, env_list));
		temp = to_delimiter(arg->name, '=');
		if (is_correct_var(arg->name))
		{
			temp_arg = get_substr(arg->name, temp);
			if (temp_arg && *temp_arg)
			{
				if ((env = get_env_by_key(temp_arg, env_list)))
				{
					str_replace(&temp_arg,
						get_substr(temp ? temp + 1 : temp, NULL));
					if (ft_strcmp(env->value, temp_arg))
						str_replace(&env->value, temp_arg);
				} else
					add_env(&env_list, temp_arg, temp && *temp ?
						get_substr(temp + 1, NULL) : NULL, 0);
			}
		}
		else
			return (ret_with_msg("export : ", arg->name, ": not a valid identifier", 1));//var is not correct
		arg_list = arg_list->next;
	}
	return (errno);
}
