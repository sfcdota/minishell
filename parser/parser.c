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

//	if (!*line)
//		return 0;
    pars.cmd1 = new_cmd();
    pars.len = ft_strlen(line);
    pars.str = malloc(sizeof(char));
    *(pars.str) = '\0';

    pars.i = -1;
    while (line[++pars.i])
    {
        while (line[pars.i] == ' ')
            pars.i++;
        if (own_strchr("\\#=()*", line[pars.i]))
            return (-1);
        if (line[pars.i] == '\'')
        {
            pars.str = strj(pars.str, line[pars.i++]);
            while (line[pars.i] != 39 && pars.i < pars.len)
                pars.str = strj(pars.str, line[pars.i++]);
            pars.str = strj(pars.str, line[pars.i]);
            if (pars.i == pars.len)
                return (-1);
            if (line[pars.i + 1] != ' ' && pars.i + 1 < pars.len)
                continue ;
        }

        if (line[pars.i] == '"')
        {
            pars.str = strj(pars.str, line[pars.i++]);
            while (line[pars.i] != 34 && pars.i < pars.len)
            {
                if (line[pars.i] == 92 && line[pars.i + 1] == 34)
                    pars.i++;
                pars.str = strj(pars.str, line[pars.i++]);
            }
            pars.str = strj(pars.str, line[pars.i]);
            if (pars.i == pars.len)
                return (-1);
            if (line[pars.i + 1] != ' ' && pars.i + 1 < pars.len)
                continue ;
        }

        if (pars.i + 2 < pars.len && line[pars.i] == '&' && line[pars.i + 1] == '&')
        {
            if (pars.str[0])
            {
                if (!pars.cmd1->name)
                    pars.cmd1->name = ft_strdup(pars.str);
                else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                    pars.cmd1->flags = pars.str;
                else
                    ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.i += 2;
            while (own_strchr("& ", line[pars.i]) && pars.i < pars.len)
                if (line[pars.i++] == '&')
                    return (-1);
            pars.cmd1->cmd_delimeter = 2;

            ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
            pars.cmd1 = new_cmd();
            free(pars.str);
            pars.str = malloc(sizeof(char) * 1);
            *pars.str = '\0';
            pars.i--;
            continue ;
        }

        if (line[pars.i] == '$')
        {
            while (!own_strchr("'\"()=#*& |;\\<>", line[pars.i]) && pars.i < pars.len)
                pars.str = strj(pars.str, line[pars.i++]);
            if (line[pars.i] == '\\')
                return (-1);
//			pars.i--;
            if (line[pars.i] != ' ' && pars.i + 1 < pars.len)
                continue ;
        }

        if (line[pars.i] == '|')
        {
            if (pars.str[0])
            {
                if (!pars.cmd1->name)
                    pars.cmd1->name = ft_strdup(pars.str);
                else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                    pars.cmd1->flags = pars.str;
                else
                    ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.str = strj(pars.str, line[pars.i++]);
            if (line[pars.i] == '|')
                pars.str = strj(pars.str, line[pars.i++]);
            while (own_strchr("| ", line[pars.i]) && pars.i < pars.len)
                if (line[pars.i++] == '|')
                    return (-1);
            if (!pars.cmd1->name)
                return (-1);
            if (pars.i == pars.len)
                return (-1);
            if (ft_strlen(pars.str) == 1)
                pars.cmd1->cmd_delimeter = 1;
            else if (ft_strlen(pars.str) == 2)
                pars.cmd1->cmd_delimeter = 3;

            ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
            pars.cmd1 = new_cmd();
            free(pars.str);
            pars.str = malloc(sizeof(char) * 1);
            *pars.str = '\0';
            pars.i--;
            continue ;
        }

        if (line[pars.i] == ';')
        {
            if (pars.str[0])
            {
                if (!pars.cmd1->name)
                    pars.cmd1->name = ft_strdup(pars.str);
                else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                    pars.cmd1->flags = pars.str;
                else
                    ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.i++;
            while (own_strchr("; ", line[pars.i]) && pars.i < pars.len)
                if (line[pars.i++] == ';')
                    return (-1);
            if (!pars.cmd1->name)
                return (-1);
            if (pars.i == pars.len)
            {
                pars.i--;
                continue ;
            }
            ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
            pars.cmd1 = new_cmd();

            pars.i--;
            continue ;
        }

        if (line[pars.i] == '<')
        {
            if (pars.str[0])
            {
                if (!pars.cmd1->name)
                    pars.cmd1->name = ft_strdup(pars.str);
                else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                    pars.cmd1->flags = pars.str;
                else
                    ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.i++;
            while (line[pars.i] == ' ' || line[pars.i] == '<')
                if (line[pars.i++] == '<')
                    return (-1);
            while (!own_strchr("'\"()$#&* |;\\<>", line[pars.i]) && line[pars.i])
                pars.str = strj(pars.str, line[pars.i++]);
            ft_lstadd_back(&pars.cmd1->redirection_list, ft_lstnew(new_redirection(ft_strdup(pars.str), 1)));
            if (pars.str)
            {
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.i--;
            continue ;
        }

        if (line[pars.i] == '>')
        {
            int type;

            if (pars.str)
            {
                if (!pars.cmd1->name)
                    pars.cmd1->name = ft_strdup(pars.str);
                else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                    pars.cmd1->flags = pars.str;
                else
                    ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            pars.str = strj(pars.str, line[pars.i++]);
            if (line[pars.i] == '>')
                pars.str = strj(pars.str, line[pars.i++]);
            while (line[pars.i] == ' ' || line[pars.i] == '>')
                if (line[pars.i++] == '>')
                    return (-1);
            if (ft_strlen(pars.str) == 1)
                type = 2;
            else
                type = 3;
            if (pars.str[0])
            {
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            while (!own_strchr("'\"()$#*& |;\\<>", line[pars.i]) && pars.i < pars.len)
                pars.str = strj(pars.str, line[pars.i++]);
            if (pars.str[0])
            {
                ft_lstadd_back(&pars.cmd1->redirection_list, ft_lstnew(new_redirection(ft_strdup(pars.str), type)));
                free(pars.str);
                pars.str = malloc(sizeof(char) * 1);
                pars.str[0] = '\0';
            }
            else
                return (-1);
            pars.i--;
            continue ;
        }

        if (!own_strchr("\"'$ |;<>()#*&\\", line[pars.i]))
        {
            while (!own_strchr("'\"()#*& |;\\<>", line[pars.i]) && line[pars.i])
                pars.str = strj(pars.str, line[pars.i++]);
            pars.i--;
            if (line[pars.i + 1] != ' ' && pars.i + 1 < pars.len)
                continue;
        }
        if (pars.str[0])
        {
            if (!pars.cmd1->name)
                pars.cmd1->name = ft_strdup(pars.str);
            else if (!pars.cmd1->flags && !pars.cmd1->arg_list && !ft_strncmp("-n", pars.str, 2))
                pars.cmd1->flags = pars.str;
            else
                ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
            free(pars.str);
            pars.str = malloc(sizeof(char) * 1);
            *pars.str = '\0';
        }
    }
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
    while (!own_strchr("$' \"", arg[j]) && arg[j])
        env_name = strj(env_name, arg[j++]);
    *i = --j;
    return (get_env_value_by_key(env_name, env_list));
}

char    *execute_$(char *arg, t_list *env_list)
{
    t_utils utils;

    utils.i = -1;
    utils.tmp = (char *)malloc(sizeof(char) * 1);
    utils.tmp[0] = '\0';
    utils.env_name = (char *)malloc(sizeof(char) * 1);
    utils.env_name[0] = '\0';
    if (!arg)
        return (NULL);
    while (arg[++utils.i])
    {
        if (arg[utils.i] == '\'')
            utils.tmp  = end_pars01(&utils, arg);
        else if (arg[utils.i] == '"')
            utils.tmp = end_pars02(&utils, arg, env_list);
        else if (arg[utils.i] == '$')
        {
            utils.tmp = end_pars03(&utils, arg, env_list);
        }
        else
            utils.tmp = strj(utils.tmp, arg[utils.i]);
    }
    free(arg);
    free(utils.env_name);
    return (utils.tmp);
}

void    end_pars(t_info *info)
{
    t_list      *cur_cmd;
    t_cmd       *cmd;
    t_list      *list;
    t_arg       *arg;

    cur_cmd = info->cmd_list;
    if (info->cmd_list)
        while (cur_cmd)
        {
            cmd = cur_cmd->content;
            list = cur_cmd->content;
            cmd->name = execute_$(cmd->name, info->env_list);
            if (!cmd->flags)
                cmd->flags = execute_$(cmd->flags, info->env_list);
            while (list)
            {
                if (cmd->arg_list)
                {
                    arg = cmd->arg_list->content;
                    arg->name = execute_$(arg->name, info->env_list);
                }
                list = list->next;
            }
            cur_cmd = cur_cmd->next;
        }
}


void	parser(char *command, t_info *info)
{
    t_cmd           *cmd;
    t_arg	        *arg;
    t_redirection   *redirection;

    if (!command)
        return ;
    cmd_count(command, info);
    end_pars(info);
    if (info->cmd_list)
        while (info->cmd_list)
        {
            cmd = info->cmd_list->content;
            while (cmd->arg_list)
            {
                arg = cmd->arg_list->content;
                cmd->arg_list = cmd->arg_list->next;
            }
            while (cmd->redirection_list)
            {
                redirection = cmd->redirection_list->content;
                cmd->redirection_list = cmd->redirection_list->next;
            }
            info->cmd_list = info->cmd_list->next;
        }

}
//  echo -n hello world ; ls -la parser.c ; pwd lol hol gol