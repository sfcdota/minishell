/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:54:27 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:54:30 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				end_cmd(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (pars->str[0])
	{
		cmd_update(pars, cmd);
	}
	pars->i++;
	while (own_strchr("; ", line[pars->i]) && pars->i < pars->len)
		if (line[pars->i++] == ';')
			return (-1);
	if (!(*cmd)->name)
		return (-1);
	if (pars->i != pars->len)
	{
		ft_lstadd_back(&(info->cmd_list), ft_lstnew((*cmd)));
		cmd = new_cmd();
	}
	pars->i--;
	return (1);
}

static int		loop_utils(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (line[pars->i] == '"' && dquote(info, pars, line) == -1)
		return (3);
	else if (pars->i + 2 < pars->len &&
			line[pars->i] == '&' && line[pars->i + 1] == '&' &&
			logical_and(info, pars, line, cmd) == -1)
		return (-1);
	else if (line[pars->i] == '|' && pipes(info, pars, line, cmd) == -1)
		return (-1);
	else if (line[pars->i] == ';' && end_cmd(info, pars, line, cmd) == -1)
		return (-1);
	else if (line[pars->i] == '<' &&
			redirection_out(info, pars, line, cmd) == -1)
		return (-1);
	else if (line[pars->i] == '>' &&
			redirection_in(info, pars, line, cmd) == -1)
		return (-1);
	return (1);
}

int				loop(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	while (line[pars->i] == ' ')
		pars->i++;
	if (own_strchr("\\#=()*", line[pars->i]))
		return (-1);
	if (line[pars->i] == '\'' && quote(info, pars, line) == -1)
		return (-1);
	else if (!own_strchr("\"' |;<>()#*&\\", line[pars->i]))
	{
		while (!own_strchr("'\"()#*& |;\\<>", line[pars->i]) && line[pars->i])
			pars->str = strj(pars->str, line[pars->i++]);
		pars->i--;
	}
	if (loop_utils(info, pars, line, cmd) == -1)
		return (-1);
	return (1);
}

void			utils_free(t_utils *utils)
{
	free(utils->tmp);
	free(utils->env_name);
}

t_pars			*pars_init(char *line)
{
	t_pars *pars;

	pars = malloc(sizeof(t_pars) * 1);
	pars->len = ft_strlen(line);
	pars->str = malloc(sizeof(char));
	*(pars->str) = '\0';
	pars->i = -1;
	return (pars);
}
