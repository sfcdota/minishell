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

#include "../executor.h"
#define GETCWD_ERROR " : Internal error. Lib func getcwd got error."

/*
** Pwd execution
*/

int	pwd(t_cmd *cmd, int fd)
{
	char *pwd;

	if (!(pwd = getcwd(NULL, 228)))
		return (ret_with_msg(cmd ? cmd->name : NULL, GETCWD_ERROR, NULL, 1));
	ft_putendl_fd(pwd, fd);
	clear_ptr((void **)&pwd);
	return (0);
}
