#include "executor.h"

int check_pwd(t_list *env_list)
{
	char *pwd;
	if (!get_env_val_by_key("PWD", env_list))
	{
		if (!(pwd = getcwd(NULL, 0)))
			return (1);
		add_env(&env_list, "PWD", pwd);
	}
	return (0);
}

int execute_cmd(char *cmd_name, t_cmd *cmd, t_list *env_list, t_info *info)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return(echo(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(cmd_name, "cd"))
		return(cd(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(cmd_name, "pwd"))
		return(pwd(cmd));
	else if (!ft_strcmp(cmd_name, "export"))
		return(export(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(cmd_name, "unset"))
		return(unset(cmd->arg_list, env_list));
	else if (!ft_strcmp(cmd_name, "env"))
		return(env(cmd, cmd->arg_list, env_list));
	else if (!ft_strcmp(cmd_name, "exit"))
		return(exit_(cmd->arg_list, env_list, info));
	else
		return(binary(cmd, cmd->arg_list, env_list, info));
	//nado dobavit result and errors
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
	int res;
	
	while (cmd_list)
	{
		cmd = ((t_cmd *)(cmd_list->content));
		cmd->name = cmd->is_env ? get_env_val_by_key(cmd->name, env_list) : cmd->name;
		uncapitalize_str(cmd->name);
		if (cmd->is_pipe)
		{
			if (!cmd_list->next)
				return (1);//error around |
			pipe(info->pipe_fd);
			if ((info->pid = fork()) == 0)
			{
				close(info->pipe_fd[0]);
				dup2(info->pipe_fd[1], 1);
				res = execute_cmd(cmd->name, cmd, env_list, info);
				close(info->pipe_fd[1]);
				exit(res);
			}
			close(info->pipe_fd[1]);
			dup2(info->pipe_fd[0], 0);
		}
		else
		{
			execute_cmd(cmd->name, cmd, env_list, info);
			wait(&res);
			close(info->pipe_fd[0]);
		}
		cmd_list = cmd_list->next;
	}
}