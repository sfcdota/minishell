#ifndef PROJECT_MINISHELL_H
# define PROJECT_MINISHELL_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# define SHELL_PREFIX "minishell> "
# define MAX_CMD_LENGTH 262144
# define REDIRECTION_IN 3
# define REDIRECTION_OUT 4
# define PIPE 5


typedef struct			s_arg
{
	char				*name;
	int					is_env;
}						t_arg;

typedef struct			s_cmd
{
	char				*name;
	int 				is_env;
	char				*flags;
	t_list				*arg_list;
	int					redirect; // 0 for empty, 1 = <, 2 = >, 3 = >>
	int					std_in;
	int					std_out;
	int					is_pipe;
}						t_cmd;

typedef struct			s_env
{
	char				*key;
	char				*value;
	int 				is_hidden;
}						t_env;

typedef struct			s_info
{
	t_list				*cmd_list;
	t_list				*env_list;
	pid_t				pid;
	int					*pipe_fd;
	char 				*line;
	char				*uncap_cmd;
	int					status;
	int 				base_in;
}						t_info;


t_arg *new_arg(char *name, int is_env);
t_cmd	*new_cmd(void);
void init_info(t_info *info, char **envp);
char *str_replace(char *s1, char *s2);
#endif