/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:01:08 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:01:08 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#define GETCWD_ERROR " : Internal error. Lib func getcwd got error."

/*
** Pwd execution
*/

int	pwd(t_cmd *cmd)
{
	char *pwd;

	if (!(pwd = getcwd(NULL, 228)))
		return (ret_with_msg(cmd->name, GETCWD_ERROR, NULL, 1));
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (0);
}
