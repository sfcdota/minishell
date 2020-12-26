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

#include "executor.h"

/*
** Trying to move to path directory with changing PWD & OLDPWD values
*/

int	go_to_dir(char *path, t_list *env_list)
{
	t_env *pwd;
	t_env *oldpwd;
	char *temp;
	char *temp_path;

	temp_path = path;
	while (temp_path && *temp_path)
		temp_path++;
	temp_path--;
	while(*temp_path == '/')
		temp_path--;
	temp_path++;
	temp = get_substr(path, temp_path);
	if (chdir(temp))
		return (1);
	pwd = get_env_by_key("PWD", env_list);
	oldpwd = get_env_by_key("OLDPWD", env_list);
	clear_ptr((void **)&oldpwd->value);
	oldpwd->value = pwd->value;
	if (oldpwd->is_hidden == 2)
		oldpwd->is_hidden = 0;
	pwd->value = getcwd(NULL, 228);
	return (errno);
}

/*
** Trying to move to CDPATH environment variable
*/

int	check_cdpath(t_cmd *cmd, char *path)
{
	char	**dirs;
	int		i;
	int		is_not_found;

	is_not_found = 1;
	i = 0;
	if (!(dirs = ft_split(path, ':')))
		return (1);
	while (dirs[i])
	{
		if (is_not_found && !chdir(dirs[i]))
			is_not_found = 0;
		i++;
	}
	ft_putstr_fd(dirs[i], cmd->out);
	while (i--)
		clear_ptr((void **)&dirs[i]);
	clear_ptr((void **)dirs);
	return (is_not_found);
}

/*
** Cd execution
*/

int	cd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char	*out;
	t_arg	*arg;

	if (args && args->next)
		return (ret_with_msg(cmd->name, ": too much arguments", NULL, 1));
	arg = args ? (t_arg *)(args->content) : NULL;
	if ((out = get_env_val_by_key("CDPATH", env_list))
	&& !check_cdpath(cmd, out))
		return (0);
	if (!args || !ft_strcmp("~", arg->name) || !ft_strcmp("--", arg->name))
		return (ret_with_msg(cmd->name, ": Something went wrong.", NULL,
			go_to_dir(get_env_val_by_key("HOME", env_list), env_list)));
	else
	{
		if (!(ft_strcmp("-", arg->name)))
			return (ret_with_msg(cmd->name
			, get_env_val_by_key("PWD", env_list), ": OLDPWD is not set"
			, go_to_dir(get_env_val_by_key("OLDPWD", env_list), env_list)));
	}
	str_replace(&arg->name, pure_$(arg->name, &info));
	str_replace(&arg->name, execute_$(arg->name, env_list));
	return (ret_with_msg(cmd->name, NULL
		, ": directory not found or unistd.h chdir function failed"
		, go_to_dir(arg->name, env_list)));
}
 