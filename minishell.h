#ifndef PROJECT_MINISHELL_H
# define PROJECT_MINISHELL_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# define MAX_CMD_LENGTH 262144
typedef struct			s_arg
{
	char				*name;
	int					is_env;
}						t_arg;

typedef struct			s_cmd
{
	char				*name;
	int					n_flag;
	t_arg				*args;
	char				*stdin;
	char				*stdout;
	int					is_separated;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct	s_info
{
	t_cmd		*cmd;
	t_env_var	*env;
}				t_info;

#endif