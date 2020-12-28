/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:01 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:02 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

void			init_info(t_info *info, char **envp)
{
	info->cmd_list = NULL;
	info->env_list = envs_to_list(envp);
	info->base_in = dup(STDIN_FILENO);
	info->pipe_fd = NULL;
	info->line = NULL;
	info->pid = -1;
	info->pipe_pid = -1;
}

t_cmd			*new_cmd(void)
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->name = NULL;
	cmd->flags = NULL;
	cmd->arg_list = NULL;
	cmd->is_env = 0;
	cmd->in = -2;
	cmd->out = -2;
	cmd->cmd_delimeter = 0;
	return (cmd);
}

t_arg			*new_arg(char *name, int is_env)
{
	t_arg *arg;

	arg = ft_calloc(sizeof(t_arg), 1);
	arg->name = name;
	arg->is_env = is_env;
	return (arg);
}

t_redirection	*new_redirection(char *filename, int type)
{
	t_redirection *redirection;

	redirection = ft_calloc(sizeof(t_redirection), 1);
	redirection->filename = filename;
	redirection->type = type;
	return (redirection);
}

void			ft_lst_elem_delete(t_list **lst, t_list *elem,
	void (*del)(void *))
{
	if (lst && *lst && elem)
	{
		if (*lst == elem)
		{
			*lst = (*lst)->next;
			if (del)
				del(elem->content);
			free(elem);
		}
		else
		{
			while (*lst && (*lst)->next != elem)
				*lst = (*lst)->next;
			if ((*lst)->next == elem)
			{
				(*lst)->next = elem->next;
				if (del)
					del(elem->content);
				free(elem);
			}
		}
	}
}
