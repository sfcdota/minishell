#include "executor.h"

int run_cmd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	if (!ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "ECHO"))
		return echo(cmd, args, env_list);
	else if (!ft_strcmp(cmd->name, "cd") || !ft_strcmp(cmd->name, "CD"))
		return cd(cmd, args, env_list);
	else if (!ft_strcmp(cmd->name, "env") || !ft_strcmp(cmd->name, "ENV"))
		return env(cmd, args, env_list);
	else if (!ft_strcmp(cmd->name, "pwd") || !ft_strcmp(cmd->name, "PWD"))
		return pwd(cmd);
	else if (!ft_strcmp(cmd->name, "export") || !ft_strcmp(cmd->name, "EXPORT"))
		return export(cmd, args, env_list);
	else if (!ft_strcmp(cmd->name, "unset") || !ft_strcmp(cmd->name, "UNSET"))
		return unset(args, env_list);
	else if (!ft_strcmp(cmd->name, "exit") || !ft_strcmp(cmd->name, "EXIT"))
		return exit_(args, env_list);
	else
		return binary(cmd, args, env_list);
}

char *cmd_to_string(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	char *cmd_str;
	t_arg *arg;
	cmd_str = NULL;
	ft_strjoin(cmd_str,cmd->name);
	ft_strjoin(cmd_str, " ");
	if (cmd->flags)
	{
		ft_strjoin(cmd_str, "-");
		ft_strjoin(cmd_str, cmd->flags);
	}
	while (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		arg->name = arg->is_env ? get_env_val_by_key(arg->name, env_list) : arg->name;
		ft_strjoin(cmd_str, arg->name);
		ft_strjoin(cmd_str," ");
		arg_list = arg_list->next;
	}
	ft_strjoin(cmd_str,"\n");
	return cmd_str;
}

int execution(t_info *info, t_list *cmd_list, t_list *env_list)
{
	t_cmd *cmd;
	char *temp;
	
	while (cmd_list)
	{
		cmd = ((t_cmd *)cmd_list->content);
		cmd->name = cmd->is_env ? get_env_val_by_key(cmd->name, env_list) : cmd->name;
		if (cmd->is_pipe)
		{
			if (!cmd_list->next)
				return (1);// error around |
			temp = cmd_to_string(cmd, cmd->arg_list, env_list);
			write(info->pipe_fd[0], temp, ft_strlen(temp));
		}
		if (info->pid == 0)
			cmd->std_out = info->pipe_fd[1];
		if (run_cmd(cmd, cmd->arg_list, env_list))
			return 1;
		cmd_list = cmd_list->next;
	}
}