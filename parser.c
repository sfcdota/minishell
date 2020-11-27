#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char		*strj(char *s1, char s2)
{
	unsigned int	i;
	char			*out_str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	if (!(out_str = malloc(sizeof(char) * (ft_strlen(s1) + 2))))
		return (NULL);
	while (s1[++i])
		out_str[i] = s1[i];
	free(s1);
	out_str[i++] = s2;
	out_str[i] = '\0';
	return (out_str);
}

static int		shite(char *line, int *i)
{
	return(line[*i] == '\\' || line[*i] == '#' || line[*i] == '=' || line[*i] == '(' ||
		line[*i] == ')' || line[*i] == '*' || line[*i] == '&');
}

int cmd_count(char *line, t_info *info)
{
	int		i;
	int		cnt;
	char	*str;
	size_t	len;
//	t_list	*cmd;
//	t_list	*cmd0;
//	t_list	*arg0;
//	t_list	*arg;
	t_cmd	*cmd1;
	t_cmd	*cmd;
	t_arg	*arg1;

	cmd1 = new_cmd();
//	ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd1));
	len = ft_strlen(line);
	cnt = 0;
	str = malloc(sizeof(char));
	i = -1;
//	cmd0 = cmd;
	while (line[++i])
	{
		if (shite(line, &i))
			return (-1);
		if (line[i] == 39)
		{
			i++;
			
			while (line[i] != 39 && i < len)
			{
				str = strj(str, line[i++]);
			}
			 if (!cmd1->name)
				 cmd1->name = ft_strdup(str);
			 else
			 	ft_lstadd_back(&cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(str), 0)));
//			printf("\t\t\t' = |%s|\n", str);
			 if (line[i + 1] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
//				 printf("\t\t\t_ = | |\n");
			free(str);
			if (i == len)
				return (-1);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			cnt++;
		}

		if (line[i] == 34)
		{
			i++;
			while(1)
			{
				while (line[i] != 34 && i < len && line[i] != 36)
				{
					if (line[i] == 92 && line[i + 1] == 34)
						i++;
					str = strj(str, line[i++]);
				}
				if (!cmd1->name)
					cmd1->name = ft_strdup(str);
				else
					ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//				printf("\t\t\t\" = |%s|\n", str);
				free(str);
				if (i == len)
					return (-1);
				 if (line[i] == 34)
				 	if (line[i + 1] == 32 && cmd1->arg_list)
				 		ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
//						 printf("\t\t\t_ = | |\n");
				str = malloc(sizeof(char) * 1);
				*str = '\0';
				cnt++;
				if (line[i] == 34)
					break ;
				i++;
				while (line[i] != 39 && line[i] != 34 && line[i] != 32 && line[i] != 36 && i < len)
					str = strj(str, line[i++]);
				ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 1)));
//				printf("\t\t\t$ = |%s|\n", str);
				free(str);
				str = malloc(sizeof(char) * 1);
				*str = '\0';
				cnt++;
			}
		}
		
		if (line[i] == 36)
		{
			if (i + 1 == len)
			{
//				str = strj(str, 36);
//				printf("\t\t\tq = |%s|\n", str);
				if (!cmd1->name)
					return (-1);
				ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 1)));
				cnt++;
				continue ;
			}

			if (line[i + 1] == 32)
			{
//				str = strj(str, 36);
//				printf("\t\t\tq = |%s|\n", str);
//				printf("\t\t\t_ = | |\n");
				if (!cmd1->name)
					return (-1);
				ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 1)));
				ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
				cnt++;
				continue ;
			}
			i++;
			while (line[i] != 39 && line[i] != 34 && line[i] != 32 &&
				   line[i] != 36 && i < len && line[i] != 124 && line[i] != 59 && line[i] != 92)
					str = strj(str, line[i++]);
			 if (!cmd1->name)
			 {
			 	cmd1->name = ft_strdup(str);
			 	cmd1->is_env = 1;
			 }
			 else
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//			printf("\t\t\t$ = |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			if (line[i] == 92)
				return (-1);
			 if (line[i] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
				 printf("\t\t\t_ = | |\n");
			cnt++;
			i--;
			continue ;
		}

		if (line[i] == 124)
		{
			str = strj(str, line[i++]);
			while (line[i] == 32 || line[i] == 124)
				if (line[i++] == 124)
					return (-1);
			 if (!cmd1->name)
			 	return (-1);
			 cmd1->is_pipe = 1;
//			 *cmd->name = *cmd1->name;
//			 cmd->is_env = cmd1->is_env;
//			 cmd->is_pipe = cmd1->is_pipe;
//			 cmd->is_separated = cmd1->is_separated;
//			 cmd->arg_list = cmd1->arg_list;
//			 cmd->flags = cmd1->flags;
//			 cmd->std_in = cmd->std_in;
//			 cmd->std_out = cmd->std_out;
			 
			 ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd1));
			 cmd1 = new_cmd();
//			printf("\t\t\t| = |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
//			 if (line[i - 1] == 32 && cmd1->arg_list)
//			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
//				printf("\t\t\t_ = | |\n");
//			cnt++;
			i--;
			continue ;
		}
		
		if (line[i] == 59)
		{
			str = strj(str, line[i++]);
			while (line[i] == 32 || line[i] == 59)
				if (line[i++] == 59)
					return (-1);
			if (!cmd1->name)
				return (-1);
			ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd1));
			cmd1 = new_cmd();
//			printf("\t\t\t; = |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
//			 if (line[i - 1] == 32/* && cmd_list->args*/)
//			// 	ft_lstadd_back(&cmd_list->args, ft_lstnew(new_arg(ft_strdup(str), 0)));
//				 printf("\t\t\t_ = | |\n");
//			cnt++;
			i--;
			continue ;
		}

		if (line[i] == 60)
		{
			str = strj(str, line[i++]);
			while (line[i] == 32 || line[i] == 60)
				if (line[i++] == 60)
					return (-1);
			 if (!cmd1->name)
				return (-1);
		 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//			printf("\t\t\t< = |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			 if (line[i - 1] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//				 printf("\t\t\t_ = | |\n");
			cnt++;
			i--;
			continue ;
		}

		if (line[i] == 62)
		{
			str = strj(str, line[i++]);
			if (line[i] == 62)
				str = strj(str, line[i++]);
			while (line[i] == 32 || line[i] == 62)
				if (line[i++] == 62)
					return (-1);
			 if (!cmd1->name)
			 	return (-1);
			 ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//			if (!ft_strncmp(str, ">>", 2))
//				printf("\t\t\t>> |%s|\n", str);
//			else if (!ft_strncmp(str, ">", 1))
//				printf("\t\t\t> |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			 if (line[i - 1] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
//				 printf("\t\t\t_ = | |\n");
			cnt++;
			i--;
			continue ;
		}

		if (line[i] != 34 && line[i] != 39 && line[i] != 32 && line[i] != 36 &&
			line[i] != 124 && line[i] != 59 && line[i] != 60 && line[i] != 62 && line[i] != 92)
		{
			while (line[i] != 32 && line[i] && line[i] != 34 && line[i] != 39 && line[i] != 36 &&
				   line[i] != 124 && line[i] != 59 && line[i] != 60 && line[i] != 62 && line[i] != 92)
				str = strj(str, line[i++]);
			 if (!cmd1->name)
			 	cmd1->name = ft_strdup(str);
			 else if (!ft_strncmp(str, "-n", 2) && !cmd1->flags && !cmd1->arg_list)
			 	cmd1->flags = ft_strdup(str);
			 else
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//			printf("\t\t\tq = |%s|\n", str);
			free(str);
			if (line[i] == 92)
				return (-1);

			 if (line[i] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
//				 printf("\t\t\t_ = | |\n");
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			cnt++;
			if (line[i] != 36)
			{
				i--;
				continue ;
			}
			while (line[i] != 39 && line[i] != 34 && line[i] != 32 && line[i] != 36 && i < len)
					str = strj(str, line[i++]);
			ft_lstadd_back(&(cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(str), 0)));
//			printf("\t\t\t$ = |%s|\n", str);
			free(str);
			str = malloc(sizeof(char) * 1);
			*str = '\0';
			 if (line[i] == 32 && cmd1->arg_list)
			 	ft_lstadd_back(&(cmd1->arg_list),  ft_lstnew(new_arg(ft_strdup(str), 0)));
//				 printf("\t\t\t_ = | |\n");
			cnt++;
			i--;
		}
	}
	ft_lstadd_back(&(info->cmd_list), ft_lstnew(cmd1));
	cmd1 = new_cmd();
	free(str);
	return (cnt);
}

void	parser(char *command, t_info *info)
{
	t_cmd	*cmd;
	t_arg	*arg;

	if (!command) 
		return ;
	printf("count = %d\n" , cmd_count(command, info));
	while (info->cmd_list->next)
	{
		cmd = info->cmd_list->content;
		while (cmd->arg_list->next)
		{
			arg = (t_arg*)cmd->arg_list->content;
			cmd->arg_list = cmd->arg_list->next;
		}
		info->cmd_list = info->cmd_list->next;
	}
	cmd = info->cmd_list->content;
	while (cmd->arg_list->next)
	{
		arg = (t_arg*)cmd->arg_list->content;
		cmd->arg_list = cmd->arg_list->next;
	}
}