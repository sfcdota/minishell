#include "executor.h"

int execute_cmd(char *cmd_name, t_cmd *cmd, t_list *env_list)
{
	if (!ft_strcmp(cmd_name, "echo"))
		echo(cmd, cmd->arg_list, env_list);
	else if (!ft_strcmp(cmd_name, "cd"))
		cd(cmd, cmd->arg_list, env_list);
	else if (!ft_strcmp(cmd_name, "pwd"))
		pwd(cmd);
	else if (!ft_strcmp(cmd_name, "export"))
		export(cmd, cmd->arg_list, env_list);
	else if (!ft_strcmp(cmd_name, "unset"))
		unset(cmd->arg_list, env_list);
	else if (!ft_strcmp(cmd_name, "env"))
		env(cmd, cmd->arg_list, env_list);
	else if (!ft_strcmp(cmd_name, "exit"))
		exit_(cmd->arg_list, env_list);
	else
		binary(cmd, cmd->arg_list, env_list);
	//nado dobavit result and errors
}

ssize_t write_to_fd(int fd, char *s)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}

int cmd_to_fd(t_cmd *cmd, int fd, t_list *arg_list, t_list *env_list)
{
	t_arg *arg;
	
	if (cmd->is_env)
	{
		write_to_fd(fd, "$");
		write_to_fd(fd, get_env_val_by_key(cmd->name, env_list));
	}
	else
		write_to_fd(fd, cmd->name);
	if (cmd->flags)
		write_to_fd(fd, cmd->flags);
	while (arg_list)
	{
		arg = ((t_arg *)(arg_list->content));
		if (arg->is_env)
		{
			write_to_fd(fd, "$");
			write_to_fd(fd, get_env_val_by_key(cmd->name,env_list));
		}
		else
			write_to_fd(fd, arg->name);
		arg_list = arg_list->next;
	}
	write_to_fd(fd, "\n");
	return (0);
}


char *cmd_to_string(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	char *cmd_str;
	t_arg *arg;
	cmd_str = NULL;
	cmd_str = ft_strjoin(cmd_str,cmd->name);
	cmd_str = ft_strjoin(cmd_str, " ");
	if (cmd->flags)
	{
		cmd_str = ft_strjoin(cmd_str, "-");
		cmd_str = ft_strjoin(cmd_str, cmd->flags);
	}
	while (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		arg->name = arg->is_env ? get_env_val_by_key(arg->name, env_list) : arg->name;
		cmd_str = ft_strjoin(cmd_str, arg->name);
		arg_list = arg_list->next;
	}
	cmd_str = ft_strjoin(cmd_str,"\n");
	return cmd_str;
}


void uncapitalize_str(char *str)
{
	while (str && *str)
	{
		if (*str >= 65 && *str <= 90)
			*str += 32;
		str++;
	}
}

int execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd *cmd;
	int *status;
	
	while (cmd_list)
	{
		cmd = ((t_cmd *)(cmd_list->content));
		cmd->name = cmd->is_env ? get_env_val_by_key(cmd->name, env_list) : cmd->name;
		uncapitalize_str(cmd->name);
		if (!info->pid)
			cmd->std_out = info->child_fd;
//		if (info->pid)
//		{
//			ft_putendl_fd("main process cmd to string:", STDOUT_FILENO);
//			ft_putendl_fd(cmd_to_string(cmd, cmd->arg_list, env_list),
//						  STDOUT_FILENO);
//		}
		if (cmd->is_pipe)
		{
			if (!cmd_list->next)
				return -1; //error
			pipe(info->pipe_fd);
			dup2(STDIN_FILENO, info->pipe_fd[0]);
			dup2(STDOUT_FILENO, info->pipe_fd[1]);
			info->pid = fork();
			ft_putnbr_fd(info->child_fd, info->pipe_fd[0]);
			cmd_to_fd(cmd, info->pipe_fd[0], cmd->arg_list, env_list);
			wait(status);
			dup2(info->pipe_fd[1], STDOUT_FILENO);
			//dup2(info->pipe_fd[0], STDIN_FILENO);
			close(info->pipe_fd[0]);
			close(info->pipe_fd[1]);
		}
		else
			execute_cmd(cmd->name, cmd, env_list);
		cmd_list = cmd_list->next;
	}
}