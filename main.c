#include "minishell.h"
#include "parser/parser.h"
#include "executor/executor.h"

void init_info(t_info *info, char **envp)
{
	info->cmd_list = NULL;
	info->env_list = envs_to_list(envp);
	info->base_in = dup(STDIN_FILENO);
	info->pid = -1;
}

int main(int argc, char **argv, char *envp[])
{
	char *line;
	t_info info;
	
	while (1)
	{
		if (write(STDOUT_FILENO, "SHELL_PREFIX ", ft_strlen("SHELL_PREFIX ")) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		if ((get_next_line(STDIN_FILENO, &line)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success)", STDOUT_FILENO);
		parser(line, &info);
		execution(&info, info.cmd_list, info.env_list);
		free(line);
	}
}
