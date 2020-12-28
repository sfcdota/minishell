/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:54:45 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:54:50 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*end_pars01(t_utils *utils, char *arg)
{
    char *tmp;

	utils->i++;
	tmp = utils->tmp;
	utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
	free(tmp);
	while (arg[utils->i] != '\'')
		utils->tmp = strj(utils->tmp, arg[utils->i++]);
	return (utils->tmp);
}

static char	*end_pars02_utils(t_utils *utils, char *arg, t_list *env_list)
{
    char    *tmp;

	if (arg[utils->i] == '$')
	{
		utils->i++;
		if (arg[utils->i] == ' ' || !arg[utils->i])
			utils->tmp = strj(utils->tmp, '$');
		else
		{
			utils->env_name = ft_strdup(get_env(&utils->i, arg, env_list));
			utils->i++;
		}
	}
	tmp = utils->tmp;
	utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
	free(tmp);
	utils->env_name = NULL;
	return (utils->tmp);
}

char		*end_pars02(t_utils *utils, char *arg, t_list *env_list)
{
	utils->i++;
	while (arg[utils->i] != '"')
	{
		while (!own_strchr("$\"", arg[utils->i]) && arg[utils->i])
		{
			if (arg[utils->i] == '\\')
			{
				utils->tmp = strj(utils->tmp, arg[utils->i + 1]);
				utils->i += 2;
			}
			utils->tmp = strj(utils->tmp, arg[utils->i++]);
		}
		utils->tmp = end_pars02_utils(utils, arg, env_list);
	}
	return (utils->tmp);
}

char		*end_pars03(t_utils *utils, char *arg, t_list *env_list)
{
    char *tmp;

	utils->i++;
	if (arg[utils->i] == ' ' || !arg[utils->i])
		utils->tmp = strj(utils->tmp, '$');
	else if (arg[utils->i] < 48 || arg[utils->i] > 57)
	{
		utils->env_name = ft_strdup(get_env(&utils->i, arg, env_list));
		tmp = utils->tmp;
		utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
		free(tmp);
	}
	free(utils->env_name);
	utils->env_name = malloc(sizeof(char) * 1);
	utils->env_name[0] = '\0';
	return (utils->tmp);
}
