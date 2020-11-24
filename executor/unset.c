#include "executor.h"

int unset(t_list *arg_list, t_list *env_list)
{
	char *cmd_name;
	t_arg *arg;
	
	while(arg_list)
	{
		arg = ((t_arg *)(arg_list->content));
		cmd_name = arg->is_env ? get_env_val_by_key(arg->name, env_list) : arg->name;
		ft_lst_elem_delete(&env_list, get_env_list_by_key(cmd_name, env_list), clear_env);
		arg_list = arg_list->next;
	}
	return (0);
}
