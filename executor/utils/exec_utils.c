/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:08:46 by cbach             #+#    #+#             */
/*   Updated: 2020/12/28 19:08:46 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "fcntl.h"

void	set_fds(t_cmd *cmd)
{
	t_redirection *redirection;

	redirection = (t_redirection *)(cmd->redirection_list->content);
	if (!redirection->filename || !*(redirection->filename))
	{
		cmd->redirection_list = cmd->redirection_list->next;
		return ;
	}
	if (redirection->type == 1)
	{
		if (cmd->in != -2)
			close(cmd->in);
		cmd->in = open(redirection->filename, O_RDONLY, 0777);
	}
	if (redirection->type == 2 || redirection->type == 3)
	{
		if (cmd->out != -2)
			close(cmd->out);
		cmd->out = open(redirection->filename, redirection->type == 2 ? 
		O_WRONLY | O_TRUNC | O_APPEND | O_CREAT
		: O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
}

void	redirection_fds(t_cmd *cmd)
{
	while (cmd->redirection_list)
	{
		set_fds(cmd);
		cmd->redirection_list = cmd->redirection_list->next;
	}
	if (cmd->out == -2)
		cmd->out = STDOUT_FILENO;
	if (cmd->in == -2)
		cmd->in = STDIN_FILENO;
}

int		pipe_init(t_cmd *cmd, t_list *cmd_list, t_list *env_list, t_info *info)
{
	int res;

	if (!cmd_list->next)
		return (258);
	info->pipe_fd = ft_calloc(2, sizeof(int));
	res = pipe(info->pipe_fd);
	if ((info->pipe_pid = fork()) == 0)
	{
		close(info->pipe_fd[0]);
		setsignals(info->pipe_pid);
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		res = execute_cmd(cmd, env_list, info);
		close(info->pipe_fd[1]);
		ft_exit(NULL, res, &g_info);
	}
	close(info->pipe_fd[1]);
	dup2(info->pipe_fd[0], 0);
	close(info->pipe_fd[0]);
	return (res);
}

int		pipe_end(t_cmd *cmd, t_list *env_list, t_info *info, int input_res)
{
	int	status;
	int	res;

	status = execute_cmd(cmd, env_list, info);
	res = input_res;
	if (info->pipe_fd)
	{
		waitpid(info->pipe_pid, &res, WUNTRACED);
		close(info->pipe_fd[0]);
		res = WEXITSTATUS(res);
	}
	if (res && !status)
		status = res;
	info->pid = -1;
	info->pipe_pid = -1;
	return (status);
}

void	return_fds(t_cmd *cmd)
{
	if (cmd->in != STDIN_FILENO)
		close(cmd->in);
	cmd->in = -1;
	if (cmd->out != STDOUT_FILENO)
		close(cmd->out);
	cmd->out = -1;
}
