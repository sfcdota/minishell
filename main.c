#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
<<<<<<< HEAD
=======
t_cmd	*new_cmd(char *name, char *flags, t_list *args, int std_in, int std_out, int is_separated, int is_bin)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = name;
	cmd->flags = flags;
	cmd->args = args;
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
>>>>>>> 2ae4d1e52f950326f1e89130ea53ec880dc0a063

int main(int argc, char **argv, char *envp[])
{
	t_info info;
<<<<<<< HEAD
	t_list t_cmd1;
	t_cmd *cmd1;
	t_list t_arg1;
	t_list t_arg2;
	t_arg *arg1;
	t_arg *arg2;
	t_list t_cmd2;
	t_cmd *cmd2;
	t_list t_arg3;
	t_list t_arg4;
	t_arg *arg3;
	t_arg *arg4;

		cmd1->name = "echo";
		cmd1->flags = "-n";

			arg1->name = "hello";
			arg1->is_env = 0;

			arg2->name = "world";
			arg2->is_env = 0;

			t_arg1.content = (void *)arg1;
			t_arg2.content = (void *)arg2;

		cmd1->args->content = &t_arg1;
		cmd1->args->next = &t_arg2;
		cmd1->std_in = 0;
		cmd1->std_out = 1;

		t_cmd1.content = (void *)cmd1;

	info.cmd = &t_cmd1;

		cmd2->name = "echo";
		cmd1->flags = "-n";

			arg3->name = "school";
			arg3->is_env = 0;

			arg4->name = "21";
			arg4->is_env = 0;

			t_arg3.content = (void *)arg3;
			t_arg4.content = (void *)arg4;

		cmd2->args->content = &t_arg3;
		cmd2->args->next = &t_arg4;
		cmd2->std_in = 0;
		cmd2->std_out = 1;

		t_cmd2.content = (void *)cmd2;

	info.cmd->next = &t_cmd1;
	printf("hello\n");
	// printf("%s\n", ((t_cmd *)(info.cmd->content))->name);
	// info.cmd = info.cmd->next;
	// printf("%s\n", ((t_cmd *)(info.cmd->content))->name);

	return (0);
}


=======
	t_cmd	*tmp;
	tmp = new_cmd(ft_strdup("echo"), ft_strdup("-n"), NULL, -1, 1, 0, 0);
	info.cmd = ft_lstnew(tmp);
	print_cmds(info.cmd);
	tmp = new_cmd(ft_strdup("sdfsf"), ft_strdup("sadf"), NULL, -1, 1, 0, 0);
	ft_lstadd_back(&(info.cmd), ft_lstnew(tmp));
	tmp = new_cmd(ft_strdup("echo"), ft_strdup(""), NULL, -1, 1, 0, 0);
	ft_lstadd_back(&(info.cmd), ft_lstnew(tmp));
	print_cmds(info.cmd);
	
	
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->name = ft_strdup("");
	cmd->flags = ft_strdup("");
	t_list *new = ft_lstnew(cmd);
	
	
	
//	else
//	{
//		char *cmd = ft_strdup("echo");
//		char *flags = ft_strdup("");
//		t_list *temp = ft_lstnew(&new_cmd(cmd, flags, -1, 1, 0, 0));
//		ft_lstadd_back(&info->cmd, temp);
//		print_cmds(info->cmd);
//	}
	// ft_putendl_fd("hui", 1);
	// add_echo(info->cmd);
	// add_echo(info.cmd);
	// add_echo(info.cmd);
	// printf("kek2");
	// print_cmds(info.cmd);
	return (0);
}
>>>>>>> 2ae4d1e52f950326f1e89130ea53ec880dc0a063
