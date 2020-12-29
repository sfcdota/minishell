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

int		set_fds(t_cmd *cmd, t_redirection *redirection)
{
	struct stat	buf;

	if (!redirection->filename || !*(redirection->filename))
		return (0);
	if (redirection->type == 1)
	{
		if (cmd->in != -2)
			close(cmd->in);
		if ((cmd->in = open(redirection->filename, O_RDONLY, 0777)) == -1)
			return (ret_with_msg(cmd->name, ": ",
				"No such file or directory", 1));
	}
	if (redirection->type == 2 || redirection->type == 3)
	{
		if (cmd->out != -2)
			close(cmd->out);
		cmd->out = open(redirection->filename, redirection->type == 2 ?
		O_WRONLY | O_TRUNC | O_APPEND | O_CREAT
		: O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	if (!ft_strcmp(redirection->filename, cmd->name) && stat(cmd->name, &buf))
		return (ret_with_msg(cmd->name, NULL, strerror(errno), errno));
	return (0);
}

int		redirection_fds(t_cmd *cmd)
{
	t_list	*redir_list;
	int		res;

	redir_list = cmd->redirection_list;
	res = 0;
	while (redir_list && !res)
	{
		res = set_fds(cmd, (t_redirection *)(redir_list->content));
		redir_list = redir_list->next;
	}
	ft_lstclear(&cmd->redirection_list, clear_redirection);
	if (cmd->out == -2)
		cmd->out = STDOUT_FILENO;
	if (cmd->in == -2)
		cmd->in = STDIN_FILENO;
	return (res);
}

int		pipe_init(t_cmd *cmd, t_list *cmd_list, t_list *env_list, t_info *info)
{
	int res;

	if (!cmd_list->next)
		return (258);
	if (info->last_piped)
		clear_ptr((void **)&info->pipe_fd);
	if (!(info->pipe_fd = ft_calloc(2, sizeof(int))))
		return (errno);
	info->last_piped = 1;
	res = pipe(info->pipe_fd);
	if ((info->pipe_pid = fork()) == 0)
	{
		close(info->pipe_fd[0]);
		setsignals(info->pipe_pid);
		dup2(info->pipe_fd[1], STDOUT_FILENO);
		res = execute_cmd(cmd->cmd_num, cmd, cmd->arg_list, env_list);
		close(info->pipe_fd[1]);
		ft_exit(NULL, res, info);
	}
	close(info->pipe_fd[1]);
	dup2(info->pipe_fd[0], STDIN_FILENO);
	close(info->pipe_fd[0]);
	return (res);
}

int		pipe_end(t_cmd *cmd, t_list *env_list, t_info *info, int input_res)
{
	int	status;
	int	res;

	status = execute_cmd(cmd->cmd_num, cmd, cmd->arg_list, env_list);
	res = input_res;
	if (info->pipe_fd)
	{
		waitpid(info->pipe_pid, &res, WUNTRACED);
		res = WEXITSTATUS(res);
		clear_ptr((void **)&info->pipe_fd);
		dup2(info->base_in, STDIN_FILENO);
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
