#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = NULL;
	cmd->flags = NULL;
	cmd->arg_list = NULL;
	cmd->is_env = 0;
	cmd->std_in = 0;
	cmd->std_out = 1;
	cmd->is_pipe = 0;
	return (cmd);
}

t_arg *new_arg(char *name, int is_env)
{
	t_arg *arg;

	arg = malloc(sizeof(t_arg));
	arg->name = name;
	arg->is_env = is_env;
	return (arg);
}