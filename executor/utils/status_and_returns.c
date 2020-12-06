/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_and_returns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:35 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:35 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
** if is_failed != 0, prints every char * parameters,
** otherwise, prints only char *message (2nd parameter)
*/

int		ret_with_msg(char *message_prefix, char *message, char *message_suffix
, int is_failed)
{
	if (is_failed)
	{
		ft_putstr_fd(message_prefix, STDOUT_FILENO);
		ft_putstr_fd(message, STDOUT_FILENO);
		ft_putendl_fd(message_suffix, STDOUT_FILENO);
	}
	else
		ft_putendl_fd(message, STDOUT_FILENO);
	return (is_failed);
}

void	errno_set(t_info *info)
{
	str_replace(get_env_by_key("?", info->env_list)->value, ft_itoa(errno));
	ft_putendl_fd(strerror(errno), STDOUT_FILENO);
}
