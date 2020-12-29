/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:54:03 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:54:08 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		quote(t_info *info, t_pars *pars, char *line)
{
	pars->str = strj(pars->str, line[pars->i++]);
	while (line[pars->i] != 39 && pars->i < pars->len)
		pars->str = strj(pars->str, line[pars->i++]);
    if (pars->i == pars->len)
        return (-1);
	pars->str = strj(pars->str, line[pars->i]);
	return (1);
}

int		dquote(t_info *info, t_pars *pars, char *line)
{
	pars->str = strj(pars->str, line[pars->i++]);
	while (line[pars->i] != 34 && pars->i < pars->len)
	{
		if (line[pars->i] == 92 && line[pars->i + 1] == 34)
			pars->i++;
		pars->str = strj(pars->str, line[pars->i++]);
	}
    if (pars->i == pars->len)
        return (-1);
	pars->str = strj(pars->str, line[pars->i]);
	return (1);
}

void	cmd_update(t_pars *pars, t_cmd **cmd)
{
	if (!(*cmd)->name)
		(*cmd)->name = ft_strdup(pars->str);
	else if (!(*cmd)->flags && !(*cmd)->arg_list
			&& !ft_strncmp("-n", pars->str, 2))
		(*cmd)->flags = ft_strdup(pars->str);
	else
		ft_lstadd_back(&(*cmd)->arg_list,
					ft_lstnew(new_arg(ft_strdup(pars->str), 0)));
	free(pars->str);
	pars->str = malloc(sizeof(char) * 1);
	pars->str[0] = '\0';
}

int		logical_and(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (pars->str[0])
	{
		cmd_update(pars, cmd);
	}
	pars->i += 2;
	while (own_strchr("& ", line[pars->i]))
		if (line[pars->i++] == '&')
			return (-1);
	if (!(*cmd)->name || pars->i >= pars->len)
		return (-1);
	(*cmd)->cmd_delimeter = 2;
	ft_lstadd_back(&(info->cmd_list), ft_lstnew((*cmd)));
	(*cmd) = new_cmd();
	free(pars->str);
	pars->str = malloc(sizeof(char) * 1);
	*pars->str = '\0';
	pars->i--;
	return (1);
}

int		pipes(t_info *info, t_pars *pars, char *line, t_cmd **cmd)
{
	if (pars->str[0])
		cmd_update(pars, cmd);
	pars->str = strj(pars->str, line[pars->i++]);
	if (line[pars->i] == '|')
		pars->str = strj(pars->str, line[pars->i++]);
	while (own_strchr("| ", line[pars->i]))
		if (line[pars->i++] == '|')
			return (-1);
	if (pars->i >= pars->len || !(*cmd)->name)
		return (-1);
	if (ft_strlen(pars->str) == 1)
		(*cmd)->cmd_delimeter = 1;
	else if (ft_strlen(pars->str) == 2)
		(*cmd)->cmd_delimeter = 3;
	ft_lstadd_back(&(info->cmd_list), ft_lstnew((*cmd)));
	*cmd = new_cmd();
	free(pars->str);
	pars->str = malloc(sizeof(char) * 1);
	*pars->str = '\0';
	pars->i--;
	return (1);
}
