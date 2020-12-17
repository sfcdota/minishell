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



int main(int argc, char **argv, char *envp[])
{
	char *line;
	t_info info;
	int res;

	init_info(&info, envp);
	setsignals(info.pid);
	while (1)
	{
		if (write(STDOUT_FILENO, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1 ||
		(res = get_next_line(STDIN_FILENO, &line)) == -1)
		{
			errno_set(&info);
			continue ;
		}
		if (res > MAX_CMD_LENGTH)
		{
			ft_putendl_fd("Cmd length over the max value of 262144 symbols", STDOUT_FILENO);
			clear_ptr((void **)&line);
			continue ;
		}
		if (res == 0 && !*line)
			ft_exit("exit", 0, &info);
		parser(line, &info);
		execution(&info, info.cmd_list, info.env_list);
		clear_ptr((void **)&line);
		ft_lstclear(&info.cmd_list, clear_cmd);
	}
}
