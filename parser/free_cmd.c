/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:36:59 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/29 22:37:03 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../executor/utils/utils.h"

int		free_cmd(t_cmd *cmd, t_pars *pars)
{
	clear_cmd(cmd);
	free(pars->str);
	free(pars);
	return (1);
}
