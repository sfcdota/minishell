/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:52 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:53 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char	*normas(char *path)
{
	int i;

	i = ft_strlen(path);
	while (i && path[i - 1] == '/')
		i--;
	return (get_substr(path, path + sizeof(char) * (i)));
}

/*
** Trying to move to path directory with changing PWD & OLDPWD values
*/

int		go_to_dir(char *path, t_list *env_list)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*temp;
	int		res;

	if (!(temp = normas(path)))
		return (1);
	res = spec_symbols(NULL, ft_strdup(temp), env_list);
	if (res != -2 || (res = chdir(temp)))
	{
		clear_ptr((void **)&temp);
		return (1);
	}
	clear_ptr((void **)&temp);
	pwd = get_env_by_key("PWD", env_list, 1);
	if ((oldpwd = get_env_by_key("OLDPWD", env_list, 1)))
	{
		clear_ptr((void **)&oldpwd->value);
		oldpwd->value = pwd && pwd->is_hidden != 2 ? pwd->value : NULL;
		pwd->is_hidden == 2 ? clear_ptr((void **)&pwd->value) : NULL;
		oldpwd->is_hidden = oldpwd->is_hidden == 2 ? 1 : oldpwd->is_hidden;
	}
	pwd->is_hidden = pwd->is_hidden == 2 ? 1 : pwd->is_hidden;
	pwd->value = getcwd(NULL, 228);
	return (0);
}

/*
** Trying to move to CDPATH environment variable
*/

int		check_cdpath(t_cmd *cmd, char *path, t_arg *arg, t_list *env_list)
{
	char	**dirs;
	int		i;
	int		is_not_found;

	is_not_found = 1;
	i = -1;
	if (!(dirs = ft_split(path, ':')))
		return (1);
	while (dirs[++i])
	{
		if (is_not_found)
		{
			str_replace(&dirs[i], normas(dirs[i]));
			if (!str_append(&dirs[i], "/") || !str_append(&dirs[i], arg->name)
			|| spec_symbols(cmd->name, ft_strdup(dirs[i]), env_list) != -2)
				is_not_found = 0;
			else if (!chdir(path) && !(is_not_found = 0))
				str_replace(&cmd->name, ft_strdup(dirs[i]));
		}
	}
	ft_putstr_fd(dirs[i], cmd->out);
	ft_clear_split(dirs, i);
	return (is_not_found);
}

int		spec_symbols(char *cmd_name, char *path, t_list *env_list)
{
	int res;

	if (!path || !ft_strcmp("~", path))
	{
		clear_ptr((void **)&path);
		return (ret_with_msg(cmd_name, NULL, ": Something went wrong.",
			go_to_dir(get_env_val_by_key("HOME", env_list, 0), env_list)));
	}
	else
	{
		if (!(ft_strcmp("-", path)))
		{
			clear_ptr((void **)&path);
			res = go_to_dir(get_env_val_by_key("OLDPWD", env_list, 0),
				env_list);
			if (res)
				return (ret_with_msg(cmd_name, NULL, ": OLDPWD not set", res));
			return (ret_with_msg(NULL, get_env_val_by_key("PWD", env_list, 0),
				NULL, 0));
		}
	}
	clear_ptr((void **)&path);
	return (-2);
}

/*
** Cd execution
*/

int		cd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char	*out;
	t_arg	*arg;
	int		res;

	if (args && args->next)
		return (ret_with_msg(cmd->name, ": too much arguments\n", NULL, 1));
	arg = args ? unname_argument(cmd->arg_list, env_list) : NULL;
	if ((out = get_env_val_by_key("CDPATH", env_list, 0))
	&& !check_cdpath(cmd, out, arg, env_list))
		return (0);
	if ((res = spec_symbols(cmd->name, normas(arg ? arg->name : NULL),
		env_list)) != -2)
		return (res);
	return (ret_with_msg(str_append(&cmd->name, ": "), NULL
		, str_append(&arg->name, ": No such file or directory")
		, go_to_dir(arg->name, env_list)));
}
