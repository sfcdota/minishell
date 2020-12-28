/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:54:16 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:54:18 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	redirection_out_utils(t_info *info, t_pars *pars, char *line)
{
	while (!own_strchr("()#&* |;\\<>", line[pars->i]) && line[pars->i])
	{
		if (line[pars->i] != '"' && line[pars->i] != '\'')
			pars->str = strj(pars->str, line[pars->i++]);
		if (line[pars->i] == '"' && dquote(info, pars, line) == -1)
			return (-1);
		else if (line[pars->i] == '"')
			pars->i++;
		if (line[pars->i] == '\'' && quote(info, pars, line) == -1)
			return (-1);
		else if (line[pars->i] == '\'')
			pars->i++;
	}
	return (1);
}

int			redirection_out(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (pars->str[0])
	{
		cmd_update(pars, cmd);
	}
	pars->i++;
	while (line[pars->i] == ' ' || line[pars->i] == '<')
		if (line[pars->i++] == '<')
			return (-1);
	if (pars->i >= pars->len)
		return (-1);
	if (redirection_out_utils(info, pars, line) == -1)
		return (-1);
	ft_lstadd_back(&(*cmd)->redirection_list,
				ft_lstnew(new_redirection(ft_strdup(pars->str), 1)));
	if (pars->str)
	{
		free(pars->str);
		pars->str = malloc(sizeof(char) * 1);
		pars->str[0] = '\0';
	}
	pars->i--;
	return (1);
}

static int	redirection_in_utils(t_pars *pars, char *line, t_cmd **cmd)
{
	if (pars->str[0])
	{
		cmd_update(pars, cmd);
	}
	pars->str = strj(pars->str, line[pars->i++]);
	if (line[pars->i] == '>')
		pars->str = strj(pars->str, line[pars->i++]);
	while (line[pars->i] == ' ' || line[pars->i] == '>')
		if (line[pars->i++] == '>')
			return (-1);
	if (pars->i >= pars->len)
		return (-1);
	if (ft_strlen(pars->str) == 1)
		pars->type = 2;
	else
		pars->type = 3;
	if (pars->str[0])
	{
		free(pars->str);
		pars->str = malloc(sizeof(char) * 1);
		pars->str[0] = '\0';
	}
	return (1);
}

static int	redirection_in_loop(t_info *info, t_pars *pars, char *line)
{
	while (!own_strchr("()#*& |;\\<>", line[pars->i]) && pars->i < pars->len)
	{
		if (line[pars->i] != '"' && line[pars->i] != '\'')
			pars->str = strj(pars->str, line[pars->i++]);
		if (line[pars->i] == '"' && dquote(info, pars, line) == -1)
			return (-1);
		else if (line[pars->i] == '"')
			pars->i++;
		if (line[pars->i] == '\'' && quote(info, pars, line) == -1)
			return (-1);
		else if (line[pars->i] == '\'')
			pars->i++;
	}
	return (1);
}

int			redirection_in(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (redirection_in_utils(pars, line, cmd) == -1)
		return (-1);
	if (redirection_in_loop(info, pars, line) == -1)
		return (-1);
	if (pars->str[0])
	{
		ft_lstadd_back(&(*cmd)->redirection_list,
				ft_lstnew(new_redirection(ft_strdup(pars->str), pars->type)));
		free(pars->str);
		pars->str = malloc(sizeof(char) * 1);
		pars->str[0] = '\0';
	}
	else
		return (-1);
	pars->i--;
	return (1);
}
