#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "executor/executor.h"
t_cmd	*new_cmd(char *name, char *flags, t_list *args, int std_in, int std_out, int is_separated)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = name;
	cmd->flags = flags;
	cmd->arg_list = args;
	cmd->std_in = std_in;
	cmd->std_out = std_out;
	cmd->is_separated = is_separated;
	return (cmd);
}
void print_cmds(t_list *cmd_list)
{
	t_cmd *cmd;
	while(cmd_list)
	{
		cmd = cmd_list->content;
		printf("printf = %d\n", printf("name = %s\nflags = %s\n", cmd->name, cmd->flags));
		cmd_list = cmd_list->next;
	}
}
void	add_echo(t_list *cmd)
{
	t_cmd	*for_short;
	for_short = (t_cmd *)(cmd->content);
	// ft_lstadd_back(&cmd, ft_lstnew(new_cmd(ft_strdup("echo"), ft_strdup(""), -1, 1, 0, 0)));
	printf("name = %s\nflags = %s\n", for_short->name, for_short->flags);
}

void	print_envp(char **envp)
{
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
}

t_arg *new_arg(char *name, int is_env)
{
	t_arg *arg;
	arg = malloc(sizeof(t_arg));
	arg->name = name;
	arg->is_env = is_env;
	return (arg);
}


void	custom_test(t_info *info, t_list *env_list)
{
	t_list *arg_list = NULL;
//	ft_lstadd_back(&arg_list, ft_lstnew(new_arg("privet poka", 0)));
//	ft_lstadd_back(&arg_list, ft_lstnew(new_arg(" ", 0)));
//	ft_lstadd_back(&arg_list, ft_lstnew(new_arg("HOME", 1)));

	ft_lstadd_back(&arg_list, ft_lstnew(new_arg(".", 1)));
	ft_lstadd_back(&arg_list, ft_lstnew(new_arg("..", 1)));
	
	ft_lstadd_back(&info->cmd_list, ft_lstnew(new_cmd("ls", NULL, arg_list, -1, 1, 0)));
	//printf("res val= %d",binary(((t_cmd *)(info->cmd_list->content)), arg_list, env_list));
}

int main(int argc, char **argv, char *envp[])
{
	char *kek;
	t_info info;
	
	pipe(info.pipe_fd);
	pid_t pid;
	kek = ft_calloc(MAX_CMD_LENGTH + 1, 1);

	if ((pid = fork()) == 0)
	{
		
		read(info.pipe_fd[0], kek, MAX_CMD_LENGTH + 1);
		//parsing
		execution(&info, info.cmd_list, info.env_list);
		free(kek);
	}
	else
	{
		kill(pid, 0);
		if (argc != 1)
		{
			ft_putendl_fd("minishell : error, arguments on minishell are not supported", 1);
			exit(1);
		}
		info.cmd_list = NULL;
		info.env_list = envs_to_list(envp);
		//custom_test(&info, info.env_list);
		//char **env = env_list_to_array(env_list);
		//print_env_array(env);
		if (argc && argv[0] && envp)
		{
			while (1)
			{
				if (write(1, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1 ||
					read(0, kek, MAX_CMD_LENGTH + 1) == -1)
					exit(-1);
				if (kek[MAX_CMD_LENGTH])
					exit(-1);
				//parsing prototype parsing(t_info *info, char *input_string)
				// to est' parsing(&info, kek);
				//execution prototype execution(t_list *cmd_list, t_list *env_list)
				//to est execution(info.cmd_list, info.env_list);
				custom_test(&info, info.env_list);
				execution(&info, info.cmd_list, info.env_list);
				ft_memset(kek, 0, MAX_CMD_LENGTH);
			}
		}
	}
	return (0);
}