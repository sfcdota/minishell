#ifndef MINISHELL_EXECUTOR_H
# define MINISHELL_EXECUTOR_H
# include "../minishell.h"
int		ft_strcmp(const char *s1, const char *s2);
char	*get_env_by_key(char *key, t_list *env_list);



/*
**
**		CMDS
**
*/
int		cd(t_cmd *cmd, t_list *args, t_list *env_list);
int		echo(t_cmd *cmd, t_list *args, t_list *env_list);
#endif
