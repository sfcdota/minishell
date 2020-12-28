/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:46 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:46 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
**						CLEAR FUNCTIONS
*/

void					clear_ptr(void **ptr);
void					clear_env(void *env_content);
void					clear_arg(void *arg_content);
void					clear_cmd(void *cmd_content);
void					clear_all(t_info *info);

/*
**						ENVIRONMENT FUNCTIONS
*/

t_env					*add_env(t_list **env_list, char *key, char *value
, int is_hidden);

void					sort_envs(t_list *env_list);
t_list					*envs_to_list(char *envp[]);
char					**env_list_to_array(t_list *env_list);
void					export_env(t_arg *arg, char *tmp, t_list *env_list);

/*
**						ENVIRONMENT "GET" FUNCTIONS
*/

char					*get_env_val_by_key(char *key, t_list *env_list);
t_env					*get_env_by_key(char *key, t_list *env_list);
t_list					*get_env_list_by_key(char *key, t_list *env_list);

/*
**						STATUS AND RETURN FUNCTIONS
*/

int						ret_with_msg(char *message_prefix, char *message
, char *message_suffix, int is_failed);

void					errno_set(t_info *info);

/*
**						STRING UTILS FUNCTIONS
*/

int						ft_strcmp(const char *s1, const char *s2);
char					*to_delimiter(char *envp_string, char delimiter);
char					*get_substr(char *begin, char *end);
char					*str_append(char **s1, char *s2);
void					str_replace(char **s1, char *s2);
void					uncapitalize_str(char *str);

t_arg					*unname_argument(t_list *arg_list, t_list *env_list);
void					unname_command(t_cmd *cmd, t_list *env_list,
	t_info *info);

int						execute_cmd(t_cmd *cmd, t_list *env_list, t_info *info);
void					redirection_fds(t_cmd *cmd);
int						pipe_init(t_cmd *cmd, t_list *cmd_list,
	t_list *env_list, t_info *info);
int						pipe_end(t_cmd *cmd, t_list *env_list, t_info *info,
	int input_res);
void					return_fds(t_cmd *cmd);
#endif
