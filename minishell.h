#ifndef PROJECT_MINISHELL_H
# define PROJECT_MINISHELL_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
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
	char				*flags;
	t_list				*args;
	int					std_in;
	int					std_out;
<<<<<<< HEAD
	// int					is_separated;
	// int					is_bin;
=======
	int					is_separated;
	int					is_bin;
>>>>>>> 2ae4d1e52f950326f1e89130ea53ec880dc0a063
}						t_cmd;

typedef struct			s_env
{
	char				*key;
	char				*value;
	int					is_hidden;
}						t_env;

typedef struct			s_info
{
	t_list				*cmd;
	t_list				*env;
}						t_info;

#endif