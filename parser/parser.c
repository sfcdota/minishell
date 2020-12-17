#include "parser.h"

char		*strj(char *s1, char s2)
{
    unsigned int	i;
    char			*out_str;

    if (!s1 || !s2)
        return (NULL);
    i = -1;
    if (!(out_str = malloc(sizeof(char) * (ft_strlen(s1) + 2))))
        return (NULL);
    while (s1[++i])
        out_str[i] = s1[i];
    free(s1);
    out_str[i++] = s2;
    out_str[i] = '\0';
    return (out_str);
}

int     own_strchr(char *str, char ch)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        if (str[i++] == ch)
            return (1);
    return (0);
}

int cmd_count(char *line, t_info *info)
{
    t_pars	pars;

    pars.cmd1 = new_cmd();
    pars.len = ft_strlen(line);
    pars.str = malloc(sizeof(char));
    *(pars.str) = '\0';
    pars.i = -1;
    while (line[++pars.i])
    {

        if (loop(info, &pars, line) == -1)
            return (-1);
        if (pars.str[0] && (line[pars.i + 1] == ' ' || line[pars.i + 1] == '>' || line[pars.i + 1] == '<'))
        {
            cmd_update(&pars);
        }
    }
    if (pars.str[0])
        cmd_update(&pars);
    ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
    pars.cmd1 = new_cmd();
    free(pars.str);
    return (1);
}
int		own_strcmp(const char *s1, const char *s2)
{
    if ((!s1 && !s2))
        return (0);
    while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*get_env_value_by_key(char *key, t_list *env_list)
{
    t_env *env;

    while (key && env_list)
    {
        env = (t_env *)(env_list->content);
        if (!own_strcmp(key, env->key))
            return (env->value);
        env_list = env_list->next;
    }
    return ("");
}

char    *get_env(int *i, char *arg, t_list *env_list)
{
    char *env_name;
    int     j;

    j = *i;
    env_name = (char *)malloc(sizeof(char) * 1);
    env_name[0] = '\0';
    while (!own_strchr("$' =\\\"", arg[j]) && arg[j])
        env_name = strj(env_name, arg[j++]);
    *i = --j;
    return (get_env_value_by_key(env_name, env_list));
}
void utils_init(t_utils *utils)
{
    utils->i = -1;
    utils->tmp = (char *)malloc(sizeof(char) * 1);
    utils->tmp[0] = '\0';
    utils->env_name = (char *)malloc(sizeof(char) * 1);
    utils->env_name[0] = '\0';
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
//    t_cmd           *cmd;
//    t_arg	        *arg;
//    t_redirection   *redirection;

    if (!command)
        return ;
    cmd_count(command, info);
//    if (info->cmd_list)
//        while (info->cmd_list)
//        {
//            cmd = info->cmd_list->content;
//            cmd->name = execute_$(cmd->name, info->env_list);
//            while (cmd->arg_list)
//            {
//                arg = cmd->arg_list->content;
//                cmd->arg_list = cmd->arg_list->next;
//            }
//            while (cmd->redirection_list)
//            {
//                redirection = cmd->redirection_list->content;
//                cmd->redirection_list = cmd->redirection_list->next;
//            }
//            info->cmd_list = info->cmd_list->next;
//        }
 
}
//  echo -n hello world ; ls -la parser.c ; pwd lol hol gol