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

char *const *arg_list_to_array(char *flags, t_list *arg_list)
{
	char **arg_array;
	
	if (flags)
	{
		ft_lstadd_back(&arg_list, ft_lstnew(new_arg(ft_strdup(flags), 0)));
	}
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

int binary(t_cmd *cmd, t_list *arg_list, t_list *env_list, t_info *info)
{
	char *filename;
	struct stat buf;
	pid_t pid;
	int retval;
	
	if ((pid = fork()) == 0)
	{
		if (!stat(cmd->name, &buf))
		{
			ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
			exit(ret_with_msg("No such command.", execve(cmd->name, arg_list_to_array(cmd->flags, arg_list),
						env_list_to_array(env_list)) == -1 ? 1 : 0));
		}
		if (!(filename = check_path(cmd, get_env_val_by_key("PATH", env_list))))
			exit(1); //unknown command
		ft_lstadd_front(&arg_list, ft_lstnew(new_arg(cmd->name, 0)));
		exit(ret_with_msg("No such command.", execve(filename, arg_list_to_array(cmd->flags, arg_list),
					env_list_to_array(env_list)) == -1 ? 1 : 0));
	}
	if (pid == -1 || wait(&retval) == -1)
		return(ret_with_msg("Fork or wait for fork to execute binary is failed.", 1));
	return retval;
}
