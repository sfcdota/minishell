#include "executor/executor.h"

void init_info(t_info *info, char **envp)
{
	info->cmd_list = NULL;
	info->env_list = envs_to_list(envp);
	info->base_in = dup(STDIN_FILENO);
	info->pipe_fd = NULL;
	info->line = NULL;
	info->pid = -1;
}

t_cmd	*new_cmd()
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
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

	arg = ft_calloc(sizeof(t_arg), 1);
	arg->name = name;
	arg->is_env = is_env;
	return (arg);
}

t_redirection *new_redirection(int type)
{
	t_redirection *redirection;

	redirection = ft_calloc(sizeof(t_redirection), 1);
	redirection->type = type;
	return (redirection);
}

char *str_replace(char *s1, char *s2)
{
	clear_ptr((void **)&s1);
	s1 = ft_strdup(s2);
	clear_ptr((void **)&s2);
	return (s1);
}