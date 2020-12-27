/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:01:03 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:01:03 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Check if str is num
*/

int	is_str_numeric(char *s)
{
	if (s && *s == '-')
		s++;
	while (s && *s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

/*
** Modified exit function with memory free of all necessary structures,
** with extra message before exit
*/

int	ft_exit(char *message, int status, t_info *info)
{
	clear_all(info);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(status);
}

/*
** Exit execution
*/

int	exit_(t_list *arg_list, t_list *env_list, t_info *info)
{
	t_arg			*arg;
	char			*code;
	long long int	kek;

	if (arg_list && arg_list->next)
	{
		ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
		return (1);
	}
	if (arg_list)
	{
		arg = ((t_arg *)(arg_list->content));
		code =  pure_$(arg->name, info);
		code = execute_$(code, env_list);
		ft_putendl_fd("exit", STDOUT_FILENO);
		kek = ft_atoi(code);
		if (!is_str_numeric(code) || (*code == '-' && !kek)
		|| (*code != '-' && kek == -1))
			ft_exit(NULL
				, ret_with_msg("exit: ", code, ": numeric argument required", 2)
				, info);
		ft_exit(NULL, kek % 256, info);
	}
	else
		ft_exit(NULL, errno, info);
}
