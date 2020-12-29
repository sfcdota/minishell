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
#include <sys/types.h>

/*
** Checks PATH env variable for binary name of cmd->name
*/

void	check_path(t_cmd *cmd, char *path)
{
	char		**dirs;
	struct stat	buf;
	int			i;
	int			is_found;

	i = 0;
	is_found = 0;
	if (!(dirs = ft_split(path, ':')))
		return ;
	while (dirs[i])
	{
		if (!is_found)
		{
			if (!str_append(&dirs[i], "/") || !str_append(&dirs[i], cmd->name))
				is_found = 1;
			if (!stat(dirs[i], &buf))
			{
				str_replace(&cmd->name, ft_strdup(dirs[i]));
				is_found = 1;
			}
		}
		i++;
	}
	ft_clear_split(dirs, i);
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
	if ((i = ft_lstsize(arg_list)))
	{
		arg_array = ft_calloc(sizeof(char *), i + 1);
		while (arg_list)
		{
			arg_array[j] = ft_strdup(((t_arg *)(arg_list->content))->name);
			if (!arg_array[j] && ((t_arg *)(arg_list->content))->name)
				return (ft_clear_split(arg_array, j));
			j++;
			arg_list = arg_list->next;
		}
		arg_array[j] = NULL;
	}
	return (i ? arg_array : NULL);
}

void	set_redirs(t_cmd *cmd)
{
	if (cmd->cmd_delimeter == 0)
	{
		if (cmd->out != STDOUT_FILENO)
			dup2(cmd->out, STDOUT_FILENO);
		if (cmd->in != STDIN_FILENO)
			dup2(cmd->in, STDIN_FILENO);
	}
}

void	clear_two_dimensional_char_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	if (!*arr)
		return (clear_ptr((void **)arr));
	while (arr[i])
	{
		clear_ptr((void **)(arr[i]));
		i++;
	}
	clear_ptr((void **)arr);
}

/*
** Binary forked execution
*/

int		binary(t_cmd *cmd, t_list *arg_list, t_list *env_list, t_info *info)
{
	struct stat	buf;
	int			retval;
	char		**temp2;
	char		**temp3;

	check_path(cmd, get_env_val_by_key("PATH", env_list, 0));
	if ((retval = stat(cmd->name, &buf)))
		return (ret_with_msg(cmd->name, NULL, NULL, 127));
	if ((info->pid = fork()) == 0)
	{
		setsignals(info->pid);
		ft_lstadd_front(&cmd->arg_list, ft_lstnew(
			new_arg(ft_strdup(cmd->name), 0)));
		temp2 = env_list_to_array(env_list);
		temp3 = arg_list_to_array(cmd->flags, cmd->arg_list);
		set_redirs(cmd);
		retval = execve(cmd->name, temp3, temp2);
		ft_clear_split(temp2, ft_lstsize(env_list));
		ft_clear_split(temp3, ft_lstsize(arg_list));
		ft_exit(NULL, retval == -1 ? 127 : 0, &g_info);
	}
	return (ret_with_msg(cmd->name, NULL, NULL, (retval == -1 ||
		info->pid == -1 || waitpid(info->pid, &retval, WUNTRACED) == -1 ||
		retval != 0) ? WEXITSTATUS(retval) : 0));
}
