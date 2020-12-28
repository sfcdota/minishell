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

void	small_error(int status, char *message)
{
	str_replace(&get_env_by_key("?", g_info.env_list)->value,
		ft_itoa(status));
	ft_putendl_fd(message, STDOUT_FILENO);
	clear_ptr((void **)&g_info.line);
	ft_lstclear(&g_info.cmd_list, clear_cmd);
}

void	clear_next(void)
{
	clear_ptr((void **)&g_info.line);
	ft_lstclear(&g_info.cmd_list, clear_cmd);
}

int		main(int argc, char **argv, char *envp[])
{
	int res;

	init_info(&g_info, envp);
	setsignals(g_info.pid);
	while (1)
	{
		if ((write(STDOUT_FILENO, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1)
		|| (res = get_next_line(g_info.base_in, &g_info.line)) == -1)
		{
			small_error(errno, strerror(errno));
			clear_ptr((void **)&res);
			continue ;
		}
		if (res == 0 && !*g_info.line)
			ft_exit("exit", 0, &g_info);
		if (res == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		if ((parser(g_info.line, &g_info)) == -1)
		{
			small_error(258, "Unexpected token");
			continue ;
		}
		execution(&g_info, g_info.cmd_list, g_info.env_list);
		clear_next();
	}
}

/*
** Show error
** ft_putstr_fd("\n\nwith status = ", STDOUT_FILENO);
** ft_putstr_fd(get_env_val_by_key("?", g_info.env_list), STDOUT_FILENO);
** ft_putendl_fd("\n", STDOUT_FILENO);
*/
