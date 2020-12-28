/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:54:57 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:55:05 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			cmd_count(char *line, t_info *info)
{
	t_pars	*pars;
	t_cmd	*cmd;

	pars = pars_init(line);
	cmd = new_cmd();
	while (line[++pars->i])
	{
		if ((loop(info, pars, line, &cmd)) == -1)
			return (-1);
		if (pars->str[0] && (pars->i >= pars->len || line[pars->i + 1] == ' ' ||
					line[pars->i + 1] == '>' || line[pars->i + 1] == '<'))
			cmd_update(pars, &cmd);
	}
	if (pars->str[0])
		cmd_update(pars, &cmd);
	ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd));
	free(pars->str);
	free(pars);
	return (1);
}

t_utils		*utils_init(void)
{
	t_utils *utils;

	utils = malloc(sizeof(t_utils) * 1);
	utils->i = -1;
	utils->tmp = (char *)malloc(sizeof(char) * 1);
	utils->tmp[0] = '\0';
	utils->env_name = (char *)malloc(sizeof(char) * 1);
	utils->env_name[0] = '\0';
	return (utils);
}

char		*pure_d(char *arg, t_info *info)
{
	t_utils	*utils;
	char	*tmp;

	if (!arg)
		return (NULL);
	utils = utils_init();
	while (arg[++utils->i])
		if (arg[utils->i] == '$')
			utils->tmp = end_pars03(utils, arg, info->env_list);
		else if (arg[utils->i] == '\'')
		{
			utils->tmp = strj(utils->tmp, arg[utils->i]);
			while (arg[++utils->i] && arg[utils->i] != '\'')
				utils->tmp = strj(utils->tmp, arg[utils->i]);
			if (arg[utils->i])
				utils->tmp = strj(utils->tmp, arg[utils->i]);
			if (!arg[utils->i])
				return (utils->tmp);
		}
		else
			utils->tmp = strj(utils->tmp, arg[utils->i]);
	tmp = ft_strdup(utils->tmp);
	utils_free(utils);
	free(utils);
	return (tmp);
}

char		*execute_d(char *arg, t_list *env_list)
{
	t_utils	*utils;
	char	*tmp;

	utils = utils_init();
	if (!arg)
		return (NULL);
	while (arg[++utils->i])
	{
		if (arg[utils->i] == '\'')
			utils->tmp = end_pars01(utils, arg);
		else if (arg[utils->i] == '"')
			utils->tmp = end_pars02(utils, arg, env_list);
		else if (arg[utils->i] == '$')
			utils->tmp = end_pars03(utils, arg, env_list);
		else
			utils->tmp = strj(utils->tmp, arg[utils->i]);
	}
	tmp = ft_strdup(utils->tmp);
	utils_free(utils);
	free(utils);
	return (tmp);
}

int			parser(char *command, t_info *info)
{
	if (!command)
		return (1);
	command = pure_d(command, info);
	return (cmd_count(command, info));
}
