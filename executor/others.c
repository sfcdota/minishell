#include "executor.h"

char *check_path(t_cmd *cmd, char *path)
{
	char **dirs;
	char *temp;
	char *temp2;
	struct stat buf;
	int i;

	i = 0;
	if (!(dirs = ft_split(path, ':')))
		return 0;
	while(dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		temp2 = ft_strjoin(temp, cmd->name);
		free(temp);
		temp = NULL;
		if(!stat(temp2, &buf))
			return (temp2);
		free(temp2);
		i++;
	}
	return (NULL);
}

char *const *arg_list_to_array(t_list *arg_list)
{
	char **arg_array;

	int j = 0;
	int i = ft_lstsize(arg_list);
	arg_array = ft_calloc(sizeof(char *), i + 1);
	while (arg_list)
	{
		arg_array[j] = ft_strdup(((t_arg *)(arg_list->content))->name);
		j++;
		arg_list = arg_list->next;
	}
	return arg_array;
}

t_list *arg_array_to_list(char **arg_array)
{
	
}

int binary(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	char *filename;
	struct stat buf;
	
	if (!stat(cmd->name, &buf))
	{
		ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
		return (execve(cmd->name, arg_list_to_array(arg_list), env_list_to_array(env_list)));
	}
	if (!(filename = check_path(cmd, get_env_val_by_key("PATH", env_list))))
		return (1); //unknown command
	ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
	return (execve(filename, arg_list_to_array(arg_list), env_list_to_array(env_list)));
}
