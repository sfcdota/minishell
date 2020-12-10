#ifndef PARSER_H
# define PARSER_H
# include "../minishell.h"

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
int         own_strchr(char *str, char ch);
void        total_pars(t_info *info);
char	    *get_env_value_by_key(char *key, t_list *env_list);
char        *get_env(int *i, char *arg, t_info *info);
char        *execute_$(char *arg, t_info *info);
int 		own_strcmp(const char *s1, const char *s2);


#endif
