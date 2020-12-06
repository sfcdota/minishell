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

void	uncapitalize_str(char *str)
{
	while (str && *str)
	{
		if (*str >= 65 && *str <= 90)
			*str += 32;
		str++;
	}
}

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

int		execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd	*cmd;
	int		res;

	while (cmd_list && (cmd = ((t_cmd *)(cmd_list->content)))->name)
	{
		//cmd = ((t_cmd *)(cmd_list->content));
		cmd->name = cmd->is_env ? get_env_val_by_key(cmd->name, env_list) : cmd->name;
		uncapitalize_str(info->uncap_cmd = ft_strdup(cmd->name));
		if (cmd->is_pipe)
		{
			if (!cmd_list->next)
				return (1);//error around |
			info->pipe_fd = ft_calloc(2, sizeof(int));
			res = pipe(info->pipe_fd);
			if ((info->pid = fork()) == 0)
			{
				setsignals(info->pid);
				close(info->pipe_fd[0]);
				dup2(info->pipe_fd[1], 1);
				res = execute_cmd(cmd, env_list, info);
				close(info->pipe_fd[1]);
				exit(res);
			}

			close(info->pipe_fd[1]);
			dup2(info->pipe_fd[0], 0);
		}
		else
		{
			res = execute_cmd(cmd, env_list, info);
			if(info->pipe_fd)
			{
				waitpid(info->pid, &res,
					WUNTRACED);//peredelat' (ili kak to obrabotat oshibki, t.k do etogo moglo bit' ne cmd->is_pipe)
				close(info->pipe_fd[0]);
			}
		}
		str_replace(get_env_by_key("?", env_list)->value, ft_itoa(res));
		clear_ptr((void **)&info->uncap_cmd);
		cmd_list = cmd_list->next;
	}
}
