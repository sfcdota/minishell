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
int         redirection_out(t_info *info, t_pars *pars, char *line)
{
    if (pars->str[0])
    {
        cmd_update(pars);
    }
    pars->i++;
    while (line[pars->i] == ' ' || line[pars->i] == '<')
        if (line[pars->i++] == '<')
            return (-1);
    while (!own_strchr("'\"()$#&* |;\\<>", line[pars->i]) && line[pars->i])
        pars->str = strj(pars->str, line[pars->i++]);
    ft_lstadd_back(&pars->cmd1->redirection_list, ft_lstnew(new_redirection(ft_strdup(pars->str), 1)));
    if (pars->str)
    {
        free(pars->str);
        pars->str = malloc(sizeof(char) * 1);
        pars->str[0] = '\0';
    }
    pars->i--;
    return (1);
}
int         redirection_in(t_info *info, t_pars *pars, char *line)
{
    if (pars->str[0])
    {
        cmd_update(pars);
    }
    pars->str = strj(pars->str, line[pars->i++]);
    if (line[pars->i] == '>')
        pars->str = strj(pars->str, line[pars->i++]);
    while (line[pars->i] == ' ' || line[pars->i] == '>')
        if (line[pars->i++] == '>')
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
    while (!own_strchr("'\"()$#*& |;\\<>", line[pars->i]) && pars->i < pars->len)
        pars->str = strj(pars->str, line[pars->i++]);
    if (pars->str[0])
    {
        ft_lstadd_back(&pars->cmd1->redirection_list, ft_lstnew(new_redirection(ft_strdup(pars->str), pars->type)));
        free(pars->str);
        pars->str = malloc(sizeof(char) * 1);
        pars->str[0] = '\0';
    }
    else
        return (-1);
    pars->i--;
    return (1);
}