#include "executor.h"

void clear_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void clear_env(void *env_content)
{
	t_env *env;
	
	env = (t_env *)env_content;
	clear_ptr(env->value);
	clear_ptr(env->key);
	clear_ptr(env);
}

void clear_args(void *arg_content)
{
	t_arg *arg;
	
	arg = (t_arg *)arg_content;
	clear_ptr(arg->name);
	clear_ptr(arg);
}

void clear_cmds(void *cmd_content)
{
	t_cmd *cmd;
	
	cmd = (t_cmd *)cmd_content;
	clear_ptr(cmd->name);
	clear_ptr(cmd->flags);
	ft_lstclear(&cmd->arg_list, clear_args);
	clear_ptr(cmd);
}

void clear_all(t_info *info)
{
	ft_lstclear(&info->cmd_list, clear_cmds);
	ft_lstclear(&info->env_list, clear_env);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	clear_ptr(info->pipe_fd);
}

int error_msg(char *message, int error_code, t_info *info)
{
	clear_all(info);
	ft_putendl_fd(message, STDOUT_FILENO);
	return (error_code);
}

int ft_exit(char *message, int status, t_info *info)
{
	clear_all(info);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(status);
}