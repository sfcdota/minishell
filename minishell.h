#ifndef PROJECT_MINISHELL_H
# define PROJECT_MINISHELL_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# define MAX_CMD_LENGTH 262144
typedef struct			s_arg
{
	char				*name;
	int					is_env;
	struct s_arg		*next;
}						t_arg;

typedef struct			s_cmd_info
{
	int					n_flag;
	t_arg				*args;
	int					stdin;
	int					stdout;
	int					is_separated;
}						t_cmd_info;

typedef struct			s_cmd
{
	char				*name;
	t_cmd_info			cmd_info;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

typedef struct	s_info
{
	t_cmd		*cmd;
	t_env_list	*env;
}				t_info;

#endif