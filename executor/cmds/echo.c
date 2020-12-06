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

int	echo(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char *out;

	while (args)
	{
		out = !((t_arg *)(args->content))->is_env ?
			((t_arg *)(args->content))->name
			: get_env_val_by_key(((t_arg *)(args->content))->name, env_list);
		args = args->next;
		if (!out || write(cmd->std_out, out, ft_strlen(out)) == -1)
			return (ret_with_msg("echo: ", "unistd write function failed"
				, NULL, 1));
	}
	return (ret_with_msg("echo: ", NULL, "unistd write function failed",
		!cmd->flags && write(cmd->std_out, "\n", 1) == -1));
}
