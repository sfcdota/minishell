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

void	check_path(t_cmd *cmd, char *path)
{
	char		**dirs;
	struct stat	buf;
	int			i;
	int 		is_found;

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
	char 		**temp2;
	char		**temp3;
	
	check_path(cmd, get_env_val_by_key("PATH", env_list));
	if (!stat(cmd->name, &buf))
	{
		if ((info->pid = fork()) == 0)
		{
			setsignals(info->pid);
			ft_lstadd_front(&cmd->arg_list, ft_lstnew(new_arg(cmd->name, 0)));
			temp2 = env_list_to_array(env_list);
			temp3 = arg_list_to_array(cmd->flags, cmd->arg_list);
			if (cmd->cmd_delimeter == 0)
			{
				if (cmd->out != STDOUT_FILENO)
					dup2(cmd->out, STDOUT_FILENO);
				if (cmd->in != STDIN_FILENO)
					dup2(cmd->in, STDIN_FILENO);
			}
			retval = execve(cmd->name, temp3, temp2);
			clear_two_dimensional_char_array(temp2);
			clear_two_dimensional_char_array(temp3);
			ft_exit(NULL, retval == -1 ? 126 : 0, &g_info);
		}
		return (ret_with_msg(cmd->name, NULL,
		" Execute binary is failed.", (info->pid == -1 ||
		waitpid(info->pid, &retval, WUNTRACED) == -1 || retval != 0) ? WEXITSTATUS(retval) : 0));
	}
	return (ret_with_msg(cmd->name, NULL, NULL, 127));
}
