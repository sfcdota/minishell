#include "executor.h"

char *check_path(t_cmd *cmd, char *path)
{
	char **dirs;
	char *temp;
	char *temp2;
	struct stat * buf;
	int i;

	i = 0;
	buf = NULL;
	if (!(dirs = ft_split(path, ':')))
		return 0;
	while(dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		temp2 = ft_strjoin(temp, cmd->name);
		free(temp);
		temp = NULL;
		if(!stat(temp2, buf))
			return (temp2);
		free(temp2);
		if (buf)
			free(buf);
		i++;
	}
	return (NULL);
}

int binary(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	char *filename;
	if (!(filename = check_path(cmd, get_env_val_by_key("PATH", env_list))))
		return (1); //unknown command
	return (execve(filename, (char * const *)ft_strdup(""), env_list_to_array(env_list)));
}
