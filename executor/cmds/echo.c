/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:58 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:58 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Echo execution
*/

int	echo(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	t_arg *arg;
	
	while (arg_list)
	{
		arg = ((t_arg *)((arg_list)->content));
		str_replace(&arg->name, pure_$(arg->name, &g_info));
		str_replace(&arg->name, execute_$(arg->name, env_list));
		if (!arg->name || write(cmd->out, arg->name, ft_strlen(arg->name)) == -1)
			return (ret_with_msg("echo: ", "unistd write function failed"
				, NULL, 1));
		if (arg->name && arg_list->next)
			write(cmd->out, " ", 1);
		arg_list = arg_list->next;
	}
	return (ret_with_msg("echo: ", NULL, "unistd write function failed",
		(!cmd->flags && write(cmd->out, "\n", 1) == -1)) ? 1 : 0);
}
