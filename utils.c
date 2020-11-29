#include "executor/executor.h"

void init_info(t_info *info, char **envp)
{
	info->cmd_list = NULL;
	info->env_list = envs_to_list(envp);
	info->base_in = dup(STDIN_FILENO);
	info->pid = -1;
}

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