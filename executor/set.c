#include "executor.h"

int set(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	print_env_list(env_list, NULL, STDOUT, LOCAL_VAR);
}