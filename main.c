#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char *envp[])
{
	t_info info;
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


