/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:27 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:27 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Clear(free) ptr
*/

void	clear_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/*
** Clear(free) environment list
*/

void	clear_env(void *env_content)
{
	t_env *env;

	env = (t_env *)env_content;
	clear_ptr((void **)&env->value);
	clear_ptr((void **)&env->key);
	clear_ptr((void **)&env);
}

/*
** Clear(free) args list
*/

void	clear_arg(void *arg_content)
{
	t_arg *arg;

	arg = (t_arg *)arg_content;
	clear_ptr((void **)&arg->name);
	clear_ptr((void **)&arg);
}

/*
** Clear(free) commands list
*/

void	clear_cmd(void *cmd_content)
{
	t_cmd *cmd;

	cmd = (t_cmd *)cmd_content;
	clear_ptr((void **)&cmd->name);
	clear_ptr((void **)&cmd->flags);
	ft_lstclear(&cmd->arg_list, clear_arg);
	clear_ptr((void **)&cmd);
}

/*
** Clear(free) g_info(shell) structure
*/

void	clear_all(t_info *info)
{
	ft_lstclear(&info->cmd_list, clear_cmd);
	ft_lstclear(&info->env_list, clear_env);
	if (info->pipe_fd)
	{
		close(info->pipe_fd[0]);
		close(info->pipe_fd[1]);
	}
	clear_ptr((void **)&info->pipe_fd);
	clear_ptr((void **)&info->line);
	clear_ptr((void **)&info->uncap_cmd);
}
