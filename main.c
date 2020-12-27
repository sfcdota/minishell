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
		parser(g_info.line, &g_info);
		execution(&g_info, g_info.cmd_list, g_info.env_list);
		clear_ptr((void **)&g_info.line);
		ft_lstclear(&g_info.cmd_list, clear_cmd);
	}
}

/*
** maybe for ^D
** if (res == 0)
** 	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
*/