/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:01:00 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:01:01 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
** Env execution
*/

int	env(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	if (arg_list)
		return (ret_with_msg("env: ", "arguments is not allowed", NULL, 1));
	print_env_list(env_list, NULL, cmd->out);
	return (errno);
}
