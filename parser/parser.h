#ifndef PARSER_H
# define PARSER_H
# include"../minishell.h"

typedef struct			s_arg
{
	char				*name;
	int					is_env;
}						t_arg;

typedef struct			s_cmd
{
	char				*name;
	char				*flags;
	int 				is_env;
	t_list				*arg_list;
	int					std_in;
	int					std_out;
	int					is_separated;
	int					is_pipe;
}						t_cmd;

typedef struct			s_env
{
	char				*key;
	char				*value;
	int					is_hidden;
}						t_env;

typedef struct			s_info
{
	t_list				*cmd_list;
	t_list				*env;
}						t_info;

typedef struct s_parser
{
	int		i;
	char	*str;
	size_t	len;
	t_cmd	*cmd1;
}			t_pars;

void		parser(char *command, t_info *info);
int			cmd_count(char *cmd, t_info *info);
char		*strj(char *s1, char s2);
t_arg		*new_arg(char *name, int is_env);
t_cmd		*new_cmd(void);

#endif
