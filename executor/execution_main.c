/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:24 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:24 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
** Main execution function
*/

int		execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd	*cmd;
	int		res;
	int		status;

	res = 0;
	status = 0;
	while (cmd_list)
	{
		cmd = ((t_cmd *)(cmd_list->content));
		redirection_fds(cmd);
		if (cmd->name)
		{
			unname_command(cmd, env_list, info);
			if (cmd->cmd_delimeter == 1)
				res = pipe_init(cmd, cmd_list, env_list, info);
			else
				status = pipe_end(cmd, env_list, info, res);
			return_fds(cmd);
			str_replace(&get_env_by_key("?", env_list)->value, ft_itoa(status));
		}
		clear_ptr((void **)&info->uncap_cmd);
		cmd_list = cmd_list->next;
	}
	return (res);
}
