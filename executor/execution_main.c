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

int		get_cmd_num(t_info *info)
{
	if (!ft_strcmp(info->uncap_cmd, "echo"))
		return (1);
	else if (!ft_strcmp(info->uncap_cmd, "cd"))
		return (2);
	else if (!ft_strcmp(info->uncap_cmd, "pwd"))
		return (3);
	else if (!ft_strcmp(info->uncap_cmd, "export"))
		return (4);
	else if (!ft_strcmp(info->uncap_cmd, "unset"))
		return (5);
	else if (!ft_strcmp(info->uncap_cmd, "env"))
		return (6);
	else if (!ft_strcmp(info->uncap_cmd, "exit"))
		return (7);
	else
		return (8);
}

int		execute_cmd(int cmd_num, t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	if (cmd_num == 1)
		return (echo(cmd, arg_list, env_list));
	else if (cmd_num == 2)
		return (cd(cmd, arg_list, env_list));
	else if (cmd_num == 3)
		return (pwd(cmd, cmd->out));
	else if (cmd_num == 4)
		return (export(cmd, arg_list, env_list));
	else if (cmd_num == 5)
		return (unset(arg_list, env_list));
	else if (cmd_num == 6)
		return (env(cmd, arg_list, env_list));
	else if (cmd_num == 7)
		return (exit_(arg_list, env_list, &g_info));
	else
		return (binary(cmd, arg_list, env_list, &g_info));
}

t_list	*next_non_pipe(t_list *cmd_list)
{
	t_cmd *cmd;

	while (cmd_list)
	{
		if (!cmd_list->next)
			return (NULL);
		cmd = ((t_cmd *)(cmd_list->content));
		if (cmd->cmd_delimeter != 1)
			break ;
		cmd_list = cmd_list->next;
	}
	return (cmd_list);
}

/*
** Main execution function
*/

int		execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd		*cmd;
	int			res;
	int			status;

	res = 0;
	while (cmd_list)
	{
		cmd = ((t_cmd *)(cmd_list->content));
		if (!(status = redirection_fds(cmd)) && cmd->name)
		{
			if (!(status = unname_command(cmd, env_list, &cmd_list, info)))
			{
				if (cmd->cmd_delimeter == 1)
					res = pipe_init(cmd, cmd_list, env_list, info);
				else
					status = pipe_end(cmd, env_list, info, res);
			}
			return_fds(cmd);
		}
		str_replace(&get_env_by_key("?", env_list, 0)->value, ft_itoa(status));
		clear_ptr((void **)&info->uncap_cmd);
		cmd_list = cmd_list ? cmd_list->next : cmd_list;
	}
	return (res);
}
