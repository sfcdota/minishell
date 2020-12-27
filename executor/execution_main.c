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
#include "fcntl.h"

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

int 	redirection_fds(t_cmd *cmd)
{
	t_redirection *redirection;
	
	while (cmd->redirection_list)
	{
		redirection = (t_redirection *)(cmd->redirection_list->content);
		if (redirection->type == 1)
		{
			if (cmd->in != -2)
				close(cmd->in);
			cmd->in = open(redirection->filename, O_RDONLY, 0666);
		}
		if (redirection->type == 2)
		{
			if (cmd->out != -2)
				close(cmd->out);
			cmd->out = open(redirection->filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0666);
		}
		if (redirection->type == 3)
		{
			if (cmd->out != -2)
				close(cmd->out);
			cmd->out =  open(redirection->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		}
		cmd->redirection_list = cmd->redirection_list->next;
	}
	if (cmd->out == -2)
		cmd->out = STDOUT_FILENO;
	if (cmd->in == -2)
		cmd->in = STDIN_FILENO;
	return (0);
}

/*
** Main execution function
*/
int		execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd	*cmd;
	int		res;
	
	res = 0;
	int status = 0;
	while (cmd_list)
	{
		cmd = ((t_cmd *)(cmd_list->content));
		redirection_fds(cmd);
		if (cmd->name)
		{
			str_replace(&cmd->name, pure_$(cmd->name, info));
			str_replace(&cmd->name, execute_$(cmd->name, env_list));
			uncapitalize_str(str_replace(&info->uncap_cmd, ft_strdup(cmd->name)));
			if (cmd->cmd_delimeter == 1)
			{
				if (!cmd_list->next)
					return (1);
				info->pipe_fd = ft_calloc(2, sizeof(int));
				res = pipe(info->pipe_fd);
				if ((info->pipe_pid = fork()) == 0)
				{
					close(info->pipe_fd[0]);
					setsignals(info->pipe_pid);
					dup2(info->pipe_fd[1], STDOUT_FILENO);
					res = execute_cmd(cmd, env_list, info);
					close(info->pipe_fd[1]);
					exit(res);
				}
				close(info->pipe_fd[1]);
				dup2(info->pipe_fd[0], 0);
			}
			else
			{
				status = execute_cmd(cmd, env_list, info);
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
			}
			if (cmd->in != STDIN_FILENO)
				close(cmd->in);
			cmd->in = -1;
			if (cmd->out != STDOUT_FILENO)
				close(cmd->out);
			cmd->out = -1;
			str_replace(&get_env_by_key("?", env_list)->value,
					ft_itoa(status));
		}
		clear_ptr((void **)&info->uncap_cmd);
		cmd_list = cmd_list->next;
	}
	return (res);
}
