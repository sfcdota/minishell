#include "minishell.h"
#include "parser/parser.h"
#include "executor/executor.h"



int main(int argc, char **argv, char *envp[])
{
	char *line;
	t_info info;
	
	init_info(&info, envp);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		if (write(STDOUT_FILENO, "SHELL_PREFIX ", ft_strlen("SHELL_PREFIX ")) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		if ((get_next_line(STDIN_FILENO, &line)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		parser(line, &info);
		execution(&info, info.cmd_list, info.env_list);
		clear_ptr(&line);
		ft_lstclear(&info.cmd_list, clear_cmds);
		info.cmd_list = NULL;
	}
}
