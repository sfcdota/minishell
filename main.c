/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:59:51 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 12:59:53 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "executor/executor.h"

//t_error			*new_error(int code, char *value)
//{
//	t_error	*error;
//
//	if ((error = ft_calloc(sizeof(t_error), 1)))
//	{
//		error->code = code;
//		error->value = value;
//	}
//	return (error);
//}
//
//t_list	init_errors(t_info *info)
//{
//	ft_lstadd_back(&info->error_list, ft_lstnew(new_error()));
//}

int	main(int argc, char **argv, char *envp[])
{
	int res;

	init_info(&g_info, envp);
	setsignals(g_info.pid);
	while (1)
	{
		if ((write(STDOUT_FILENO, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1)
		|| (res = get_next_line(g_info.base_in, &g_info.line)) == -1)
		{
			str_replace(&get_env_by_key("?", g_info.env_list)->value,
				ft_itoa(errno));
			strerror(errno);
			continue ;
		}
		if (res > MAX_CMD_LENGTH)
		{
			ft_putendl_fd("Cmd length over  262144 symbols", STDOUT_FILENO);
			clear_ptr((void **)&g_info.line);
			continue ;
		}
		if (res == 0 && !*g_info.line)
			ft_exit("exit", 0, &g_info);
		if (res == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		res = parser(g_info.line, &g_info);
		if (res != 1)
			str_replace(&get_env_by_key("?", g_info.env_list)->value,
				ft_itoa(258));
		execution(&g_info, g_info.cmd_list, g_info.env_list);
		clear_ptr((void **)&g_info.line);
		ft_lstclear(&g_info.cmd_list, clear_cmd);
		ft_putstr_fd("\n\nwith status = ", STDOUT_FILENO);
		ft_putstr_fd(get_env_val_by_key("?", g_info.env_list), STDOUT_FILENO);
		ft_putendl_fd("\n", STDOUT_FILENO);
	}
}

/*
** maybe for ^D
** if (res == 0)
** 	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
*/