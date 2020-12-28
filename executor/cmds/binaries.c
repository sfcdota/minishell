/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:50 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:50 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** Checks PATH env variable for binary name of cmd->name
*/

char	*check_path(t_cmd *cmd, char *path)
{
	char		**dirs;
	char		*temp;
	struct stat	buf;
	int			i;

	i = 0;
	temp = NULL;
	if (!(dirs = ft_split(path, ':')))
		return (0);
	while (dirs[i])
	{
		if (!str_append(&dirs[i], "/") || !str_append(&dirs[i], cmd->name))
			break ;
		if (!stat(dirs[i], &buf))
		{
			temp = ft_strdup(dirs[i]);
			break ;
		}
		i++;
	}
	while (i >= 0)
		clear_ptr((void **)&dirs[i--]);
	clear_ptr((void **)dirs);
	return (temp);
}

/*
** Casts argument list to an array for putting to execve as argument
*/

char	**arg_list_to_array(char *flags, t_list *arg_list)
{
	char	**arg_array;
	int		j;
	int		i;

	if (flags)
	{
		ft_lstadd_back(&arg_list, ft_lstnew(new_arg(ft_strdup(flags), 0)));
	}
	j = 0;
	i = ft_lstsize(arg_list);
	arg_array = ft_calloc(sizeof(char *), i + 1);
	while (arg_list)
	{
		arg_array[j] = ft_strdup(((t_arg *)(arg_list->content))->name);
		j++;
		arg_list = arg_list->next;
	}
	return (arg_array);
}

/*
** Binary forked execution
*/

int		binary(t_cmd *cmd, t_list *arg_list, t_list *env_list, t_info *info)
{
	struct stat	buf;
	int			retval;
	char		*temp;

	if ((info->pid = fork()) == 0)
	{
		setsignals(info->pid);
		if (cmd->cmd_delimeter == 0)
		{
			if (cmd->out != STDOUT_FILENO)
				dup2(cmd->out, STDOUT_FILENO);
			if (cmd->in != STDIN_FILENO)
				dup2(cmd->in, STDIN_FILENO);
		}
		ft_lstadd_front(&cmd->arg_list, ft_lstnew(new_arg(cmd->name, 0)));
		if ((temp = check_path(cmd, get_env_val_by_key("PATH", env_list))))
			str_replace(&cmd->name, temp);
		if (!stat(cmd->name, &buf))
			ft_exit(NULL, execve(cmd->name, arg_list_to_array(cmd->flags,
				cmd->arg_list), env_list_to_array(env_list)) == -1 ? 126 : 0, &g_info);
		ft_exit(NULL, 127, &g_info);
	}
	return (ret_with_msg(cmd->name, NULL, " : No such command / Execute binary"
		" is failed.", (info->pid == -1 || waitpid(info->pid, &retval,
			WUNTRACED) == -1 || retval != 0) ? WEXITSTATUS(retval) : 0));
}
