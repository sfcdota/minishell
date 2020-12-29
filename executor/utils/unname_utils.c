/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:36:50 by cbach             #+#    #+#             */
/*   Updated: 2020/12/28 18:36:50 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

t_arg	*unname_argument(t_list *arg_list, t_list *env_list)
{
	t_arg *arg;

	arg = (t_arg *)(arg_list->content);
	str_replace(&arg->name, pure_d(arg->name, &g_info));
	str_replace(&arg->name, execute_d(arg->name, env_list));
	return (arg);
}

int		unname_command(t_cmd *cmd, t_list *env_list, t_list **cmd_list,
	t_info *info)
{
	struct stat	buf;

	str_replace(&cmd->name, pure_d(cmd->name, &g_info));
	str_replace(&cmd->name, execute_d(cmd->name, env_list));
	clear_ptr((void **)info->uncap_cmd);
	info->uncap_cmd = ft_strdup(cmd->name);
	uncapitalize_str(info->uncap_cmd);
	cmd->cmd_num = get_cmd_num(info);
	if (cmd->cmd_num == 8)
	{
		check_path(cmd, get_env_val_by_key("PATH", env_list, 0));
		if ((stat(cmd->name, &buf)))
		{
			*cmd_list = next_non_pipe((*cmd_list)->next ? (*cmd_list)->next :
				*cmd_list);
			return (ret_with_msg(cmd->name, NULL, NULL, 127));
		}
	}
	return (0);
}
