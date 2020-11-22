#ifndef MINISHELL_EXECUTOR_H
# define MINISHELL_EXECUTOR_H
# include "../minishell.h"
int		ft_strcmp(const char *s1, const char *s2);
char	*get_env_val_by_key(char *key, t_list *env_list);
t_env	*get_env_by_key(char *key, t_list *env_list);
t_env	*add_env(t_list **env_list, char *key, char *value, int is_hidden);
t_list	*envs_to_list(char *envp[]);
char *get_substr(char *begin, char *end);
char *to_delimiter(char *envp_string, char delimiter);
char	**env_list_to_array(t_list *env_list);
void print_env_list(t_list *env_list, char *prefix, int std_out);
void	print_env_array(char **envp);
int binary(t_cmd *cmd, t_list *arg_list, t_list *env_list);

/*
**
**		CMDS
**
*/
int		cd(t_cmd *cmd, t_list *args, t_list *env_list);
int		echo(t_cmd *cmd, t_list *args, t_list *env_list);
int unset(t_list *arg_list, t_list *env_list);
int env(t_cmd *cmd, t_list *arg_list, t_list *env_list);
int export(t_cmd *cmd, t_list *arg_list, t_list *env_list);
int pwd(t_cmd *cmd);
int exit_(t_list *arg_list, t_list *env_list);

void	*ft_clear_split(char **t, int i);


int error_msg(char *message, int error_code, t_info *info);


int execution(t_info *info, t_list *cmd_list, t_list *env_list);
#endif
