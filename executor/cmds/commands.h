/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:00:55 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 13:00:56 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

/*
**							SHELL COMMANDS
*/
int		echo(t_cmd *cmd, t_list *arg_list, t_list *env_list);
int		env(t_cmd *cmd, t_list *arg_list, t_list *env_list);
int		pwd(t_cmd *cmd, int fd);
int		export(t_cmd *cmd, t_list *arg_list, t_list *env_list);
int		cd(t_cmd *cmd, t_list *args, t_list *env_list);
int		exit_(t_list *arg_list, t_list *env_list, t_info *info);
int		unset(t_list *arg_list, t_list *env_list);
int		binary(t_cmd *cmd, t_list *arg_list, t_list *env_list, t_info *info);

/*
**					USABLE UTILS FROM COMMANDS FUNCTIONS
*/
void	print_env_list(t_list *env_list, char *prefix, int std_out);
void	ft_exit(char *message, int status, t_info *info);
int		is_correct_var(char *s);
int		spec_symbols(char *cmd_name, char *path, t_list *env_list);
void	check_path(t_cmd *cmd, char *path);
#endif
