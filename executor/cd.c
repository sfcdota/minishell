#include "executor.h"

int error(char *message, int err)
{
	ft_putendl_fd(message, 1);
	return (err);
}

int change(char *path, t_list *env_list)
{
	t_env *pwd;
	t_env *oldpwd;
	t_env *temp;
	t_env *temp2;
	
	if (chdir(path) || (!(pwd = get_env_by_key("PWD", env_list)) &&
	(!(temp = add_env(&env_list, "PWD", "")))))
		return (1);
	if (!(oldpwd = get_env_by_key("OLDPWD", env_list)) &&
	(!(temp2 = add_env(&env_list, "OLDPWD", ""))))
	{
		if (!pwd)
			free(temp);
		return (1);
	}
	if (!pwd)
		ft_lstadd_back(&env_list, ft_lstnew(temp));
	if (!oldpwd)
		ft_lstadd_back(&env_list, ft_lstnew(temp2));
	pwd = temp;
	oldpwd = temp2;
	oldpwd->value = pwd->value;
	pwd->value = path;
	return (0);
}


int check_cdpath(t_cmd *cmd, char *path)
{
	char **dirs;
	int i;
	
	i = 0;
	if (!(dirs = ft_split(path, ':')))
		return -1;
	while(dirs[i])
	{
		if (!chdir(dirs[i]))
			break ;
		i++;
	}
	if (dirs[i]) // mojno ubrat t.k pri dirs[i] = null putstr niche ne sdelaet
		ft_putstr_fd(dirs[i], cmd->std_out);
	return (0);
}


int cd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char *out;
	
	if (args && args->next)
		return (ret_with_msg(cmd->name, ": unistd.h write function failed", NULL, 1));
	if (!args || 
	ft_strcmp("~",((t_arg *)(args->content))->name) ||
	ft_strcmp("--",((t_arg *)(args->content))->name))
		return (chdir(get_env_val_by_key("HOME", env_list)));
	if (!(ft_strcmp("-",((t_arg *)(args->content))->name)))
	{
		if (!chdir(get_env_val_by_key("OLDPWD", env_list)))
		{
			ft_putendl_fd(get_env_val_by_key("OLDPWD", env_list), cmd->std_out);
			return (0);
		}
		return (ret_with_msg(cmd->name, ": OLDPWD is not set", NULL, 1));
	}
	if ((out = get_env_val_by_key("CDPATH", env_list)) && !check_cdpath(cmd, out))
		return (0);
	out = !((t_arg *)(args->content))->is_env ? ((t_arg *)(args->content))->name
	: get_env_val_by_key(((t_arg *) (args->content))->name, env_list);
	if (chdir(out ? out : get_env_val_by_key("HOME", env_list)) == -1)
		return (ret_with_msg(cmd->name, ": unistd.h chdir function failed", NULL, 1));
	return (0);
}