/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbach <cbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:59:57 by cbach             #+#    #+#             */
/*   Updated: 2020/12/06 12:59:58 by cbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_MINISHELL_H
# define PROJECT_MINISHELL_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# define SHELL_PREFIX "minishell> "

typedef struct			s_arg
{
	char				*name;
	int					is_env;
}						t_arg;

/*
** type: 0 for empty, 1 = <, 2 = <<, 3 = >, 4 = >>
*/
typedef struct			s_redirection
{
	char				*filename;
	int					type;
}						t_redirection;

/*
** cmd_delimiter: 0 for empty, 1 for pipe, 2 for &&, 3 for ||
*/
typedef struct			s_cmd
{
	char				*name;
	int					is_env;
	char				*flags;
	t_list				*arg_list;
	t_list				*redirection_list;
	int					in;
	int					out;
	int					cmd_delimeter;
}						t_cmd;

typedef struct			s_env
{
	char				*key;
	char				*value;
	int					is_hidden;
}						t_env;

typedef struct			s_error
{
	int					code;
	char				*value;
}						t_error;

typedef struct			s_info
{
	t_list				*cmd_list;
	t_list				*env_list;
	t_list				*error_list;
	pid_t				pid;
	pid_t				pipe_pid;
	int					*pipe_fd;
	char				*line;
	char				*uncap_cmd;
	int					status;
	int					base_in;
}						t_info;

t_info					g_info;

t_arg					*new_arg(char *name, int is_env);
t_cmd					*new_cmd(void);
void					init_info(t_info *info, char **envp);
t_redirection			*new_redirection(char *filename, int type);
void					ft_lst_elem_delete(t_list **lst, t_list *elem,
	void (*del)(void *));
t_list					init_errors(t_info *info);
#endif
