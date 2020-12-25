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

#include "executor.h"

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
			temp = dirs[i];
			break ;
		}
		i++;
	}
	while (i--)
		clear_ptr((void **)&dirs[i]);
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
	char		*filename;
	struct stat	buf;
	int			retval;

	if ((info->pid = fork()) == 0)
	{
		setsignals(info->pid);
		if (!stat(cmd->name, &buf))
		{
			ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
			exit(ret_with_msg(NULL, "Binary execution had error.\n", NULL
				, execve(cmd->name, arg_list_to_array(cmd->flags, arg_list)
				, env_list_to_array(env_list)) == -1 ? 1 : 0));
		}
		if (!(filename = check_path(cmd, get_env_val_by_key("PATH", env_list))))
			exit(ret_with_msg(cmd->name, " : ", "No such command.", 1));
		ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
		exit(ret_with_msg(NULL, "Binary execution had error.\n", NULL
			, execve(filename, arg_list_to_array(cmd->flags, arg_list)
			, env_list_to_array(env_list)) == -1 ? 1 : 0));
	}
	return (ret_with_msg(cmd->name, NULL
		, " : Fork or wait for fork to execute binary is failed."
		, info->pid == -1 || waitpid(info->pid, &retval, WUNTRACED) == -1));
}
