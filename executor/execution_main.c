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
** Executes command by comparing command name
*/

int		execute_cmd(t_cmd *cmd, t_list *env_list, t_info *info)
{
	if (!ft_strcmp(info->uncap_cmd, "echo"))
		return (echo(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(info->uncap_cmd, "cd"))
		return (cd(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(info->uncap_cmd, "pwd"))
		return (pwd(cmd));
	else if (!ft_strcmp(info->uncap_cmd, "export"))
		return (export(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(info->uncap_cmd, "unset"))
		return (unset(cmd->arg_list, env_list));
	else if (!ft_strcmp(info->uncap_cmd, "env"))
		return (env(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(info->uncap_cmd, "exit"))
		return (exit_(cmd->arg_list, env_list, info));
	else
		return (binary(cmd, cmd->arg_list, env_list, info));
}

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
