#include "executor.h"

char *get_env_by_key(char *key, t_env_list *env_list)
{
	while(env_list)
	{
		if(!ft_strcmp(key, env_list->key))
			return (ft_strdup(env_list->value));
		env_list = env_list->next;
	}
	return (NULL);
}


int echo(t_cmd_info *info, t_arg *args, t_env_list *env_list)
{
	char *out;
	
	while (args)
	{
		out = !args->is_env ? args->name : get_env_by_key(args->name, env_list);
		if (!out || write(info->stdout, out, ft_strlen(out)) == -1)
			return (1);
		args = args->next;
	}
	if (!info->n_flag && write(info->stdout, "\n", 1) == -1)
		return (1);
	return (0);
}