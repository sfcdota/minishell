#include "parser.h"

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
	t_pars	pars;

//	if (!*line)
//		return 0;
	pars.cmd1 = new_cmd();
	pars.len = ft_strlen(line);
	pars.str = malloc(sizeof(char));
	*(pars.str) = '\0';
	pars.i = -1;
	while (line[++pars.i])
	{
		if (shite(line, &pars.i))
			return (-1);
		if (line[pars.i] == 39)
		{
			pars.i++;
			
			while (line[pars.i] != 39 && pars.i < pars.len)
			{
				pars.str = strj(pars.str, line[pars.i++]);
			}
			 if (!pars.cmd1->name)
				 pars.cmd1->name = ft_strdup(pars.str);
			 else
			 	ft_lstadd_back(&pars.cmd1->arg_list, ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			 if (line[pars.i + 1] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
			free(pars.str);
			if (pars.i == pars.len)
				return (-1);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
		}

		if (line[pars.i] == 34)
		{
			pars.i++;
			while(1)
			{
				while (line[pars.i] != 34 && pars.i < pars.len && line[pars.i] != 36)
				{
					if (line[pars.i] == 92 && line[pars.i + 1] == 34)
						pars.i++;
					pars.str = strj(pars.str, line[pars.i++]);
				}
				if (!pars.cmd1->name)
					pars.cmd1->name = ft_strdup(pars.str);
				else
					ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
				free(pars.str);
				if (pars.i == pars.len)
					return (-1);
				 if (line[pars.i] == 34)
				 	if (line[pars.i + 1] == 32 && pars.cmd1->arg_list)
				 		ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
				pars.str = malloc(sizeof(char) * 1);
				*pars.str = '\0';
				if (line[pars.i] == 34)
					break ;
				pars.i++;
				while (line[pars.i] != 39 && line[pars.i] != 34 && line[pars.i] != 32 && line[pars.i] != 36 && pars.i < pars.len)
					pars.str = strj(pars.str, line[pars.i++]);
				ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 1)));
				free(pars.str);
				pars.str = malloc(sizeof(char) * 1);
				*pars.str = '\0';
			}
		}
		
		if (line[pars.i] == 36)
		{
			if (pars.i + 1 == pars.len)
			{
				if (!pars.cmd1->name)
					return (-1);
				ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup("$"), 0)));
				continue ;
			}

			if (line[pars.i + 1] == 32)
			{
				if (!pars.cmd1->name)
					return (-1);
				ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup("$"), 0)));
				ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
				continue ;
			}
			pars.i++;
			while (line[pars.i] != 39 && line[pars.i] != 34 && line[pars.i] != 32 &&
				   line[pars.i] != 36 && pars.i < pars.len && line[pars.i] != 124 && line[pars.i] != 59 && line[pars.i] != 92)
				pars.str = strj(pars.str, line[pars.i++]);
			 if (!pars.cmd1->name)
			 {
				 pars.cmd1->name = ft_strdup(pars.str);
				 pars.cmd1->is_env = 1;
			 }
			 else
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 1)));
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			if (line[pars.i] == 92)
				return (-1);
			 if (line[pars.i] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
			pars.i--;
			continue ;
		}

		if (line[pars.i] == 124)
		{
			pars.str = strj(pars.str, line[pars.i++]);
			while (line[pars.i] == 32 || line[pars.i] == 124)
				if (line[pars.i++] == 124)
					return (-1);
			 if (!pars.cmd1->name)
			 	return (-1);
			pars.cmd1->is_pipe = 1;
			 
			 ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
			pars.cmd1 = new_cmd();
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			pars.i--;
			continue ;
		}
		
		if (line[pars.i] == 59)
		{
			pars.str = strj(pars.str, line[pars.i++]);
			while (line[pars.i] == 32 || line[pars.i] == 59)
				if (line[pars.i++] == 59)
					return (-1);
			if (!pars.cmd1->name)
				return (-1);
			ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
			pars.cmd1 = new_cmd();
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			pars.i--;
			continue ;
		}

		if (line[pars.i] == 60)
		{
			pars.str = strj(pars.str, line[pars.i++]);
			while (line[pars.i] == 32 || line[pars.i] == 60)
				if (line[pars.i++] == 60)
					return (-1);
			 if (!pars.cmd1->name)
				return (-1);
			ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			 if (line[pars.i - 1] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			pars.i--;
			continue ;
		}

		if (line[pars.i] == 62)
		{
			pars.str = strj(pars.str, line[pars.i++]);
			if (line[pars.i] == 62)
				pars.str = strj(pars.str, line[pars.i++]);
			while (line[pars.i] == 32 || line[pars.i] == 62)
				if (line[pars.i++] == 62)
					return (-1);
			 if (!pars.cmd1->name)
			 	return (-1);
			 ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			 if (line[pars.i - 1] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
			pars.i--;
			continue ;
		}

		if (line[pars.i] != 34 && line[pars.i] != 39 && line[pars.i] != 32 && line[pars.i] != 36 &&
			line[pars.i] != 124 && line[pars.i] != 59 && line[pars.i] != 60 && line[pars.i] != 62 && line[pars.i] != 92)
		{
			while (line[pars.i] != 32 && line[pars.i] && line[pars.i] != 34 && line[pars.i] != 39 && line[pars.i] != 36 &&
				   line[pars.i] != 124 && line[pars.i] != 59 && line[pars.i] != 60 && line[pars.i] != 62 && line[pars.i] != 92)
				pars.str = strj(pars.str, line[pars.i++]);
			 if (!pars.cmd1->name)
				 pars.cmd1->name = ft_strdup(pars.str);
			 else if (!ft_strncmp(pars.str, "-n", 2) && !pars.cmd1->flags && !pars.cmd1->arg_list)
				 pars.cmd1->flags = ft_strdup(pars.str);
			 else
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			free(pars.str);
			if (line[pars.i] == 92)
				return (-1);

			 if (line[pars.i] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(" "), 0)));
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			if (line[pars.i] != 36)
			{
				pars.i--;
				continue ;
			}
			while (line[pars.i] != 39 && line[pars.i] != 34 && line[pars.i] != 32 && line[pars.i] != 36 && pars.i < pars.len)
				pars.str = strj(pars.str, line[pars.i++]);
			ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			free(pars.str);
			pars.str = malloc(sizeof(char) * 1);
			*pars.str = '\0';
			 if (line[pars.i] == 32 && pars.cmd1->arg_list)
			 	ft_lstadd_back(&(pars.cmd1->arg_list), ft_lstnew(new_arg(ft_strdup(pars.str), 0)));
			pars.i--;
		}
	}
	ft_lstadd_back(&(info->cmd_list), ft_lstnew(pars.cmd1));
	pars.cmd1 = new_cmd();
	free(pars.str);
	return (1);
}

void	parser(char *command, t_info *info)
{
	t_cmd	*cmd;
	t_arg	*arg;

	if (!command) 
		return ;
	cmd_count(command, info);
//	while (info->cmd_list->next)
//	{
//		cmd = info->cmd_list->content;
//		while (cmd->arg_list->next)
//		{
//			arg = (t_arg*)cmd->arg_list->content;
//			cmd->arg_list = cmd->arg_list->next;
//		}
//		info->cmd_list = info->cmd_list->next;
//	}
//	cmd = info->cmd_list->content;
//	while (cmd->arg_list->next)
//	{
//		arg = (t_arg*)cmd->arg_list->content;
//		cmd->arg_list = cmd->arg_list->next;
//	}
}
//  echo -n hello world ; ls -la parser.c ; pwd lol hol gol