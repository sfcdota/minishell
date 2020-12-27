/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:21 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:22 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTOR_H
# define MINISHELL_EXECUTOR_H
# include "../minishell.h"
# include "utils/utils.h"
# include "cmds/commands.h"
# include "../parser/parser.h"

/*
**		MAIN SHELL COMMAND
*/
int		execution(t_info *info, t_list *cmd_list, t_list *env_list);

/*
**		SIGNAL FUNCTIONSS
*/
void	sighandler(int signum);
void	sighandler_child(int signum);
void	setsignals(pid_t pid);

#endif
