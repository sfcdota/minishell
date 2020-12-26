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

/*
** Check if var has valid name
*/

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

int		extra_argument(char *arg_name, t_list *arg_list, t_arg *arg)
{
	int is_exist;
	char **temp;
	t_list *new;
	
	is_exist = 0;
	new = NULL;
	while (arg_name && *arg_name && *arg_name == ' ')
		arg_name++;
	while (arg_name && *arg_name && *arg_name != ' ')
		arg_name++;
	while (!is_exist && arg_name && *arg_name)
	{
		if (*arg_name == ' ')
		{
			arg->name = str_replace(&arg->name, get_substr(arg->name, arg_name));
			temp = ft_split(arg_name, ' ');
			is_exist = !is_exist;
			while (temp && *temp)
				ft_lstadd_back(&new, ft_lstnew(temp++));
			if (arg_list->next)
				new->next = arg_list->next;
			arg_list->next = new;
		}
		else
			arg_name++;
	}
	return (is_exist);
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
		str_replace(&arg->name, pure_$(arg->name, &info));
		str_replace(&arg->name, execute_$(arg->name, env_list));
		temp = to_delimiter(arg->name, '=');
//		if (extra_argument(temp ? temp + 1 : temp, arg_list, arg));
//			temp = to_delimiter(arg->name, '=');
		if (is_correct_var(arg->name))
		{
			temp_arg = get_substr(arg->name, temp);
			if ((env = get_env_by_key(temp_arg, env_list)))
			{
				str_replace(&temp_arg, get_substr(temp ? temp + 1 : temp, NULL));
				if (ft_strcmp(env->value, temp_arg))
					str_replace(&env->value, temp_arg);
			}
			else
				add_env(&env_list, temp_arg,
					get_substr(temp ? temp + 1 : temp, NULL), 0);
		}
		else
			return (ret_with_msg("export : ", arg->name, ": not a valid identifier", 1));//var is not correct
		arg_list = arg_list->next;
	}
	return (errno);
}
