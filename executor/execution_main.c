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
** Modifying str to lower register symbols
*/

void	uncapitalize_str(char *str)
{
	while (str && *str)
	{
		ft_tolower(*str);
		str++;
	}
}

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
			if (cmd->std_in)
				if (cmd->std_in != 0)
					close(cmd->std_in);
6			dup2(open(redirection->filename, O_RDONLY), STDIN_FILENO);
//			if ((info.base_in = open(redirection->filename, O_RDONLY)) == -1)
//				return (ret_with_msg("minishell: ",redirection->filename,
//					": No such file or directory", 1));
		}
		if (redirection->type == 2)
		{
			if (cmd->std_out)
				if (cmd->std_out != 1)
					close(cmd->std_out);
			if ((cmd->std_out = open(redirection->filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT)) == -1)
				return (ret_with_msg("minishell: ",redirection->filename,
					": File creation failed", 1));
		}
		if (redirection->type == 3)
		{
			if (cmd->std_out)
				if (cmd->std_out != 1)
					close(cmd->std_out);
			if ((cmd->std_out = open(redirection->filename, O_WRONLY | O_APPEND | O_CREAT)) == -1)
				return (ret_with_msg("minishell: ",redirection->filename,
					": File creation failed", 1));
		}
		cmd->redirection_list = cmd->redirection_list->next;
	}
	return (0);
}

/*
** Main execution function
*/

int		execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd	*cmd;
	int		res;

	while (cmd_list && (cmd = ((t_cmd *)(cmd_list->content)))->name)
	{
		//cmd = ((t_cmd *)(cmd_list->content));
		str_replace(&cmd->name, execute_$(cmd->name, env_list));
		uncapitalize_str(info->uncap_cmd = ft_strdup(cmd->name));
		redirection_fds(cmd);
		if (cmd->cmd_delimeter == 1)
		{
			if (!cmd_list->next)
				return (1);//error around |
			info->pipe_fd = ft_calloc(2, sizeof(int));
			res = pipe(info->pipe_fd);
			if ((info->pid = fork()) == 0)
			{
				setsignals(info->pid);
				close(info->pipe_fd[0]);
				dup2(info->pipe_fd[1], info->base_in);
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
					WUNTRACED);//peredelat' (ili kak to obrabotat oshibki, t.k do etogo moglo bit' ne cmd->cmd_delimeter)
				close(info->pipe_fd[0]);
			}
		}
		str_replace(&get_env_by_key("?", env_list)->value, ft_itoa(res));
		clear_ptr((void **)&info->uncap_cmd);
		if (cmd->std_in != 0)
			close(cmd->std_in);
		if (cmd->std_out != 1)
			close(cmd->std_out);
		cmd_list = cmd_list->next;
	}
}
