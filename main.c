#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "executor/executor.h"

t_info info;

t_cmd	*new_cmd(char *name, char *flags, t_list *args, int std_in, int std_out, int is_pipe)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = name;
	cmd->flags = flags;
	cmd->arg_list = args;
	cmd->std_in = std_in;
	cmd->std_out = std_out;
	cmd->is_pipe = is_pipe;
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
	t_list *arg_list1 = NULL;
	t_list *arg_list2 = NULL;

//	ft_lstadd_back(&arg_list, ft_lstnew(new_arg("privet poka", 0)));
//	ft_lstadd_back(&arg_list, ft_lstnew(new_arg(" ", 0)));
	//ft_lstadd_back(&arg_list2, ft_lstnew(new_arg("-e", 0)));
	
	//ft_lstadd_back(&arg_list, ft_lstnew(new_arg("", 1)));
	//ft_lstadd_back(&arg_list1, ft_lstnew(new_arg(" ", 0)));
	ft_lstadd_back(&arg_list1, ft_lstnew(new_arg(ft_strdup(".."), 0)));
	
	ft_lstadd_back(&info->cmd_list, ft_lstnew(new_cmd(ft_strdup("ls"), ft_strdup("-rR"), arg_list1, 0, 1, 1)));
	ft_lstadd_back(&info->cmd_list, ft_lstnew(new_cmd(ft_strdup("cat"), ft_strdup("-e"), arg_list2, 0, 1, 0)));
	//printf("res val= %d",binary(((t_cmd *)(info->cmd_list->content)), arg_list, env_list));
}


void sig_child_handler(int signum)
{
	if (signum == SIGINT)
		ft_putendl_fd("", STDOUT_FILENO);
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(SIGQUIT, STDOUT_FILENO);
	}
	exit(0);
}


void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\r", info.base_in);
//		execve(info.argv[0], info.argv, info.envp);
//		exit_(NULL, info.env_list, &info);
	}
	if (signum == SIGQUIT)
		ft_putstr_fd("\b\b''''", STDIN_FILENO);

}

/*
 * 
 * 				FOR CHILD PROCESSES ONLY
 * 
 */
//SIGINT = ctrl + C : interrupt process (as kill)
//$? = 146: command not found


//SIGQUIT = ctrl + \ : quit as soon as possible without saving info and put msg like this
//^\zsh: quit       ls -rR /
//$? = 131: command not found

/*
 * 
 * 				FOR MAIN PROCESS ONLY
 * 
 */

// END OF TRANSMISSION, EOF = ctrl + D  = exit when zero input and print exit

int main(int argc, char **argv, char *envp[])
{
	char *line;
	int res;
	int i = 0;
	info.argv = argv;
	
	if (argc != 1 && argv)
	{
		ft_putendl_fd("minishell : error, arguments on minishell are not supported",1);
		exit(1);
	}
	info.pipe_fd = ft_calloc(2, 1);
	info.pid = -10;
	info.cmd_list = NULL;
	info.env_list = envs_to_list(envp);
	info.envp = envp;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	check_pwd(info.env_list);
	info.base_in = dup(STDIN_FILENO);
	while (1)
	{
		if (write(STDOUT_FILENO, SHELL_PREFIX, ft_strlen(SHELL_PREFIX)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success", STDOUT_FILENO);
		if ((res = get_next_line(info.base_in, &line)) == -1)
			ft_putendl_fd("I/O error. Read/write was not success", STDOUT_FILENO);
		if (res == 0 && ft_strlen(line) == 0) //EOF (CTRL + D) handling
			ft_exit("exit", 0, &info);
		//parser
		if (!i)
			custom_test(&info, info.env_list);
		execution(&info, info.cmd_list, info.env_list);
		free(line);
		ft_lstclear(&info.cmd_list, clear_cmds);
		i++;
	}
}