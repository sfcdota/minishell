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
** Instrument for return function allowing to put message before return value
** if is_failed != 0, prints every char * parameters,
** otherwise, prints only char *message (2nd parameter)
*/

int		ret_with_msg(char *message_prefix, char *message, char *message_suffix
, int is_failed)
{
	if (is_failed == 1)
	{
		ft_putstr_fd(message_prefix, STDOUT_FILENO);
		ft_putstr_fd(message, STDOUT_FILENO);
		ft_putendl_fd(message_suffix, STDOUT_FILENO);
	}
	else if (!is_failed)
		ft_putendl_fd(message, STDOUT_FILENO);
	else
		strerror(is_failed);
	return (is_failed);
}

/*
** Sets $? environment variable to an errno value
*/

void	errno_set(t_info *info)
{
	str_replace(&get_env_by_key("?", info->env_list)->value, ft_itoa(errno));
	strerror(errno);
}
