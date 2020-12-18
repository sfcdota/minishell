#include "parser.h"

int         end_cmd(t_info *info, t_pars *pars, char *line)
{
    if (pars->str[0])
    {
        cmd_update(pars);
    }
    pars->i++;
    while (own_strchr("; ", line[pars->i]) && pars->i < pars->len)
        if (line[pars->i++] == ';' || !pars->cmd1->name)
            return (-1);
    if (pars->i != pars->len)
    {
        ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars->cmd1));
        pars->cmd1 = new_cmd();
    }
    pars->i--;
    return (1);
}

int         loop(t_info *info, t_pars *pars, char *line)
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
    else if (line[pars->i] == '"' && dquote(info, pars, line) == -1)
        return (-1);
    else if (pars->i + 2 < pars->len && line[pars->i] == '&' && line[pars->i + 1] == '&' && logical_and(info, &pars, line) == -1)
        return (-1);
    else if (line[pars->i] == '|' && pipes(info, pars, line) == -1)
        return (-1);
    else if (line[pars->i] == ';' && end_cmd(info, pars, line) == -1)
        return (-1);
    else if (line[pars->i] == '<' && redirection_out(info, pars, line) == -1)
        return (-1);
    else if (line[pars->i] == '>' && redirection_in(info, pars, line) == -1)
        return (-1);
    return (1);
}