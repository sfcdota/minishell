#include "parser.h"

char *end_pars01(t_utils *utils, char *arg) {
    utils->i++;
    utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
    while (arg[utils->i] != '\'')
        utils->tmp = strj(utils->tmp, arg[utils->i++]);
    return (utils->tmp);
}

char *end_pars02(t_utils *utils, char *arg, t_list *env_list) {
    utils->i++;
    while (arg[utils->i] != '"') {
        while (!own_strchr("$\"", arg[utils->i]) && arg[utils->i])
            utils->tmp = strj(utils->tmp, arg[utils->i++]);
        if (arg[utils->i] == '$') {
            utils->i++;
            if (arg[utils->i] == ' ' || !arg[utils->i])
                utils->tmp = strj(utils->tmp, '$');
            else {
                utils->env_name = get_env(&utils->i, arg, env_list);
                utils->i++;
            }
        }
        utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
    }
    return (utils->tmp);
}

char *end_pars03(t_utils *utils, char *arg, t_list *env_list) {
    utils->i++;
    if (arg[utils->i] == ' ' || !arg[utils->i])
        utils->tmp = strj(utils->tmp, '$');
    else {
        utils->env_name = get_env(&utils->i, arg, env_list);
        utils->tmp = ft_strjoin(utils->tmp, utils->env_name);
    }
    return (utils->tmp);
}