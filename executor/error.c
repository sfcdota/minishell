#include "executor.h"

void clear_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void clear_env(void *env_content)
{
	t_env *env;
	
	env = (t_env *)env_content;
	clear_ptr((void **)&env->value);
	clear_ptr((void **)&env->key);
	clear_ptr((void **)&env);
}

void clear_args(void *arg_content)
{
	t_arg *arg;
	
	arg = (t_arg *)arg_content;
	clear_ptr((void **)&arg->name);
	clear_ptr((void **)&arg);
}

void clear_cmds(void *cmd_content)
{
	t_cmd *cmd;
	
	cmd = (t_cmd *)cmd_content;
	clear_ptr((void **)&cmd->name);
	clear_ptr((void **)&cmd->flags);
	ft_lstclear(&cmd->arg_list, clear_args);
	clear_ptr((void **)&cmd);
}

void clear_all(t_info *info)
{
	ft_lstclear(&info->cmd_list, clear_cmds);
	ft_lstclear(&info->env_list, clear_env);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	clear_ptr((void **)&info->pipe_fd);
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

int ret_with_msg(char *message_prefix, char *message, char *message_suffix, int retval)
{
	if (retval)
	{
		ft_putstr_fd(message_prefix, STDOUT_FILENO);
		ft_putstr_fd(message, STDOUT_FILENO);
		ft_putendl_fd(message_suffix, STDOUT_FILENO);
	}
	return (retval);
}