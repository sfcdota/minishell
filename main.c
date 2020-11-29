#include "minishell.h"
#include "parser/parser.h"
#include "executor/executor.h"



int main(int argc, char **argv, char *envp[])
{
	char *line;
	t_info info;
	int res;
	
	init_info(&info, envp);
	while (1)
	{
		setsignals(info.pid);
		if (write(STDOUT_FILENO, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		if ((res = get_next_line(STDIN_FILENO, &line)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		if (res > MAX_CMD_LENGTH)
		{
			ft_putendl_fd("Cmd length over the max value of 262144 symbols", STDOUT_FILENO);
			clear_ptr((void **)&line);
			continue ;
		}
		if (res == 0 && !*line)
			ft_exit("exit", 0, &info);
		parser(line, &info);
		execution(&info, info.cmd_list, info.env_list);
		clear_ptr((void **)&line);
		ft_lstclear(&info.cmd_list, clear_cmds);
	}
}
