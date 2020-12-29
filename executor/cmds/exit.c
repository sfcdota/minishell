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

int		is_str_numeric(char *s)
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

void	ft_exit(char *message, int status, t_info *info)
{
	clear_all(info);
	ft_putendl_fd(message, STDOUT_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit(status);
}

/*
** Exit execution
*/

int		exit_(t_list *arg_list, t_list *env_list, t_info *info)
{
	t_arg			*arg;
	long long int	kek;

	if (arg_list && arg_list->next)
	{
		ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
		return (1);
	}
	if (arg_list)
	{
		arg = unname_argument(arg_list, env_list);
		ft_putendl_fd("exit", STDOUT_FILENO);
		kek = ft_atoi(arg->name);
		if (!is_str_numeric(arg->name) || (*arg->name == '-' && !kek)
		|| (*arg->name != '-' && kek == -1))
			ft_exit(NULL, ret_with_msg("exit: ", arg->name,
			": numeric argument required", 255), info);
		ft_exit(NULL, kek % 256, info);
	}
	else
		ft_exit(NULL, 0, info);
	return (0);
}
