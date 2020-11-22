#include "executor.h"

int change(char *path, t_list *env_list)
{
	t_env *pwd;
	t_env *oldpwd;
	t_env *temp;
	t_env *temp2;
	
	if (chdir(path) || (!(pwd = get_env_by_key("PWD", env_list)) &&
	(!(temp = add_env(&env_list, "PWD", "", 1)))))
		return (1);
	if (!(oldpwd = get_env_by_key("OLDPWD", env_list)) &&
	(!(temp2 = add_env(&env_list, "OLDPWD", "", 1))))
	{
		if (!pwd)
			free(temp);
		return (1);
	}
	if (!pwd)
		ft_lstadd_back(&env_list, ft_lstnew(temp));
	if (!oldpwd)
		ft_lstadd_back(&env_list, ft_lstnew(temp2));
	pwd =  pwd ? pwd : temp;
	oldpwd = oldpwd ? oldpwd : temp2;
	oldpwd->value = pwd->value;
	if (!(getcwd(pwd->value, 228)))
		return (1);
	return (0);
}


int check_cdpath(t_cmd *cmd, char *path)
{
	char **dirs;
	int i;
	int is_found;
	
	i = 0;
	is_found = 0;
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
	if (dirs[i])
		is_found = 1;
	ft_clear_split(dirs, i);
	return (is_found);
}


int cd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char *out;
	
	if (args->next)
		return (1);//need output message (too much arguments)
	if (!((t_arg *)(args->content))->name || 
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
		return (1);
	}
	if ((out = get_env_val_by_key("CDPATH", env_list)) && check_cdpath(cmd, out))
		return (0);
	out = !((t_arg *)(args->content))->is_env ? ((t_arg *)(args->content))->name
	: get_env_val_by_key(((t_arg *) (args->content))->name, env_list);
	if (chdir(out ? out : get_env_val_by_key("HOME", env_list)) == -1)
		return (1); //need output message (hz, chdir ne udalsya)
	return (0);
}