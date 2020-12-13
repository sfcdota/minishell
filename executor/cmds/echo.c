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

#include "executor.h"

/*
** Echo execution
*/

int	echo(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	char *out;
	t_arg *arg;
	while (arg_list)
	{
		arg = ((t_arg *)((arg_list)->content));
		str_replace(arg->name, execute_$(arg->name, env_list));
		arg_list = arg_list->next;
		if (!arg->name || write(cmd->std_out, out, ft_strlen(out)) == -1)
			return (ret_with_msg("echo: ", "unistd write function failed"
				, NULL, 1));
	}
	return (ret_with_msg("echo: ", NULL, "unistd write function failed",
		!cmd->flags && write(cmd->std_out, "\n", 1) == -1));
}
