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

int cmd_count(char *line, t_info *info)
{
    t_pars	*pars;

    pars = malloc(sizeof(t_pars));
    pars->cmd1 = new_cmd();
    pars->len = ft_strlen(line);
    pars->str = malloc(sizeof(char));
    *(pars->str) = '\0';
    pars->i = -1;
    while (line[++pars->i])
    {
        if (loop(info, pars, line) == -1)
            return (-1);
        if (pars->str[0] && (line[pars->i + 1] == ' ' || line[pars->i + 1] == '>' || line[pars->i + 1] == '<'))
            cmd_update(pars);
    }
    if (pars->str[0])
        cmd_update(pars);
    ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars->cmd1));
    pars->cmd1 = new_cmd();
    free(pars->str);
    return (1);
}

void utils_init(t_utils *utils)
{
    utils->i = -1;
    utils->tmp = (char *)malloc(sizeof(char) * 1);
    utils->tmp[0] = '\0';
    utils->env_name = (char *)malloc(sizeof(char) * 1);
    utils->env_name[0] = '\0';
}

char    *pure_$(char *arg, t_info *info)
{
    t_utils *utils;

    if (!arg)
    	return (NULL);
    utils = malloc(sizeof(t_utils));
    utils_init(utils);
    while (arg[++utils->i])
        if (arg[utils->i] == '$')
            utils->tmp = end_pars03(utils, arg, info->env_list);
        else if (arg[utils->i] == '\'')
        {
            utils->tmp = strj(utils->tmp, arg[utils->i]);
            while (arg[++utils->i] != '\'' || !arg[utils->i])
                utils->tmp = strj(utils->tmp, arg[utils->i]);
            utils->tmp = strj(utils->tmp, arg[utils->i]);
            if (!arg[utils->i])
                return (utils->tmp);
        }
        else
            utils->tmp = strj(utils->tmp, arg[utils->i]);
    return (utils->tmp);
}


char    *execute_$(char *arg, t_list *env_list)
{
    t_utils *utils;

    utils = malloc(sizeof(t_utils));
    utils_init(utils);
    if (!arg)
        return (NULL);
    while (arg[++utils->i])
    {
        if (arg[utils->i] == '\'')
            utils->tmp  = end_pars01(utils, arg);
        else if (arg[utils->i] == '"')
            utils->tmp = end_pars02(utils, arg, env_list);
        else if (arg[utils->i] == '$')
            utils->tmp = end_pars03(utils, arg, env_list);
        else
            utils->tmp = strj(utils->tmp, arg[utils->i]);
    }
    free(utils->env_name);
    return (utils->tmp);
}

void	parser(char *command, t_info *info)
{
    if (!command)
        return ;
//    command = pure_$(command, g_info);
    cmd_count(command, info);
}
