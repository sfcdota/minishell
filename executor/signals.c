/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:18 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:19 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
** Sets sighandler for the main(parent) process
*/

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(SHELL_PREFIX, STDOUT_FILENO);
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

/*
** Sets sighandler for the child process(es)
*/

void	sighandler_child(int signum)
{
	if (signum == SIGINT)
	{

	}
	if (signum == SIGQUIT)
	{

	}
}

/*
** Sets sighandler by pid
*/

void	setsignals(pid_t pid)
{
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
}

/*
 *
 * SIGQUIT (ctrl + \) in main : does nothing, in child : print "^\Quit" and exits (must be a core dump, but no funcs allowed for that),
 * maybe it's possible to implement with kill
 *
 *
 * SIGINT (ctrl + c) in child : print ^C and exits, in main : print ^C and wait for the next line
 *
 *
 * EOF (ctrl + d) in child : does nothing, in main : print "exit" and exits
 *
 */
