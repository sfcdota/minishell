#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "executor/executor.h"
t_cmd	*new_cmd(char *name, char *flags, t_list *args, int std_in, int std_out, int is_separated, int is_bin)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = name;
	cmd->flags = flags;
	cmd->arg_list = args;
	cmd->std_in = std_in;
	cmd->std_out = std_out;
	cmd->is_separated = is_separated;
	cmd->is_bin = is_bin;
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

int main(int argc, char **argv, char *envp[])
{
	char *kek;
	
	t_list *env_list = envs_to_list(envp);
	char **env = env_list_to_array(env_list);
	print_env_array(env);
//	if (argc && argv[0] && envp)
//	{
//		kek = ft_calloc(MAX_CMD_LENGTH + 1, 1);
//		while (1)
//		{
//			if (write(1, "minishell> ", 2) == -1 ||
//				read(0, kek, MAX_CMD_LENGTH + 1) == -1)
//				exit(-1);
//			if (kek[MAX_CMD_LENGTH])
//				exit(-1);
//			if (!ft_strncmp(kek, "exit\n", MAX_CMD_LENGTH))
//				exit(0);
//			//parsing
//			//execution
//			ft_memset(kek, 0, MAX_CMD_LENGTH);
//		}
//	}
	return (0);
}