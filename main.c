#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void print_cmds(t_list *cmd_list)
{
	t_cmd *cmd;
	t_arg *arg;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		arg = cmd->arg_list->content;
		printf("printf = %d\n\n", printf("name = %s\nflags = %s\narg_name = %s\narg_is_env = %d\n",
										 cmd->name, cmd->flags, arg->name, arg->is_env));
		cmd_list = cmd_list->next;
	}
}

void example(t_info *info)
{
//	t_cmd	*cmd_list;
//
//	cmd_list = new_cmd(ft_strdup("echo"), ft_strdup("-n"), NULL, -1, 1, 0, 0);
//	info->cmd_list = ft_lstnew(cmd_list);
//	cmd_list = new_cmd(ft_strdup("sdfsf"), ft_strdup("sadf"), NULL, -1, 1, 0, 0);
//	ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd_list));
//	cmd_list = new_cmd(ft_strdup("echo"), ft_strdup(""), NULL, -1, 1, 0, 0);
//	ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd_list));
	print_cmds(info->cmd_list);
}


int main(int argc, char **argv, char *envp[])
{
	char *line;
	t_info info;
	int res;
	t_list *cmds;
	t_cmd *cmd;
	t_list *arg_list;
	t_arg *arg;
	while (1)
	{
		if (write(STDOUT_FILENO, "SHELL_PREFIX ", ft_strlen("SHELL_PREFIX ")) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		if ((res = get_next_line(STDIN_FILENO, &line)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		parser(line, &info);
//		while(info.cmd_list)
//		{
//			cmd = ((t_cmd *)info.cmd_list->content);
//			arg = ((t_arg *)cmd->arg_list->content);
//			info.cmd_list = info.cmd_list->next;
//		}
		free(line);
	}
}
