#include "executor.h"

int echo(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char *out;
	
	while (args)
	{
		out = !((t_arg *)(args->content))->is_env ? 
		((t_arg *)(args->content))->name :
			  get_env_val_by_key(((t_arg *) (args->content))->name, env_list);
		if (!out || write(cmd->std_out, out, ft_strlen(out)) == -1)
			return (1);
		args = args->next;
	}
	if (!cmd->flags && write(cmd->std_out, "\n", 1) == -1)
		return (1);
	return (0);
}