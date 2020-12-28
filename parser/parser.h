/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerrica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:55:24 by ljerrica          #+#    #+#             */
/*   Updated: 2020/12/25 09:55:27 by ljerrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../minishell.h"

typedef struct s_parser
{
	int		i;
	int     type;
	char	*str;
	size_t	len;
}			t_pars;

typedef struct s_utils
{
    char    *tmp;
    char    *env_name;
    int     i;
}           t_utils;

int		parser(char *command, t_info *info);
int			cmd_count(char *cmd, t_info *info);
char		*strj(char *s1, char s2);
t_arg		*new_arg(char *name, int is_env);
t_cmd		*new_cmd(void);
t_utils		*utils_init();
int         own_strchr(char *str, char ch);
char	    *get_env_value_by_key(char *key, t_list *env_list);
char        *get_env(int *i, char *arg, t_list *env_list);
char        *execute_$(char *arg, t_list *env_list);
int 		own_strcmp(const char *s1, const char *s2);
char        *end_pars01(t_utils *utils, char *arg);
char        *end_pars02(t_utils *utils, char *arg, t_list *env_list);
char        *end_pars03(t_utils *utils, char *arg, t_list *env_list);
int         quote(t_info *info, t_pars *pars, char *line);
int         dquote(t_info *info, t_pars *pars, char *line);
void        cmd_update(t_pars *pars, t_cmd *cmd);
int         logical_and(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
int         pipes(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
int         end_cmd(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
int         redirection_out(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
int         redirection_in(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
int         loop(t_info *info, t_pars *pars, char *line, t_cmd *cmd);
char        *pure_$(char *arg, t_info *info);
void 		utils_free(t_utils *utils);
t_pars		*pars_init(char *line);

#endif
