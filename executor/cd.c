#include "executor.h"

int cd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	int res;
	char *out;
	
	if (args->next)
		return (1);//need output message (too much arguments)
	if (get_env_by_key("CDPATH", env_list))
		
	out = !((t_arg *)(args->content))->is_env ? ((t_arg *)(args->content))->name
	: get_env_by_key(((t_arg *)(args->content))->name, env_list);
	res = chdir(out ? out : get_env_by_key("HOME", env_list));
	if (res == -1)
		return (1); //need output message (hz, chdir ne udalsya)
	return (0);
}