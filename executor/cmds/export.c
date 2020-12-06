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

#include "executor.h"

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
			if (env->value && *env->value)
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

int		is_correct_var(char *s)
{
	if (ft_isdigit(*s))
		return (0);
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

int		export(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	t_arg *arg;
	char *var_str;
	char *temp;
	char *temp_arg;
	t_env *env;

	if (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		var_str = arg->is_env ? get_env_val_by_key(arg->name, env_list) : arg->name;
		if (!(to_delimiter(var_str, '=') + 1) && arg_list->next)
		{
			arg_list = arg_list->next;
			arg = (t_arg *)(arg_list->content);
			str_append(&var_str,
				arg->is_env ? get_env_val_by_key(arg->name, env_list)
							: arg->name);
		}
		if (is_correct_var(var_str))
		{
			temp = to_delimiter(var_str, '=');
			if ((env = get_env_by_key(temp_arg = get_substr(var_str, temp), env_list)))
			{
				clear_ptr((void **)&env->value);
				env->value = get_substr(temp ? temp + 1 : temp, NULL);
			}
			else
				add_env(&env_list, get_substr(var_str, temp),
					get_substr(temp ? temp + 1 : temp, NULL), 0);
			clear_ptr((void **)&temp_arg);
		}
		else
			return (ret_with_msg("export : ", var_str, ": not a valid identifier", 1));//var is not correct
	}
	else
		print_env_list(env_list, "declare -x ", cmd->std_out);
	return (0);
}
