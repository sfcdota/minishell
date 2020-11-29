#include "executor.h"

int env(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	if (arg_list)
		return (ret_with_msg("env: ", "arguments is not allowed", NULL, 1));//args is not part of the subject
	print_env_list(env_list, NULL, cmd->std_out);
	return (0);
}
