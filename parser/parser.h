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

typedef struct s_utils
{
    char    *tmp;
    char    *env_name;
    int     i;
}           t_utils;

void		parser(char *command, t_info *info);
int			cmd_count(char *cmd, t_info *info);
char		*strj(char *s1, char s2);
t_arg		*new_arg(char *name, int is_env);
t_cmd		*new_cmd(void);
int         own_strchr(char *str, char ch);
void        end_pars(t_info *info);
char	    *get_env_value_by_key(char *key, t_list *env_list);
char        *get_env(int *i, char *arg, t_list *env_list);
char        *execute_$(char *arg, t_list *env_list);
int 		own_strcmp(const char *s1, const char *s2);
char        *end_pars01(t_utils *utils, char *arg);
char        *end_pars02(t_utils *utils, char *arg, t_list *env_list);
char        *end_pars03(t_utils *utils, char *arg, t_list *env_list);

#endif
