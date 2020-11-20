#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_arg	*new_arg(char *name, int is_env)
{
	t_arg *arg;

	arg = malloc(sizeof(t_arg));
	arg->name = name;
	arg->is_env = is_env;
	return (arg);
}

t_cmd	*new_cmd(char *name, char *flags, t_list *args, int std_in, int std_out, int is_separated, int is_bin)
{
	t_cmd *cmd;
	t_arg *arg;

	arg = new_arg("hello", 0);
	cmd = malloc(sizeof(t_cmd));
	cmd->name = name;
	cmd->flags = flags;
	cmd->args = ft_lstnew(arg);
	cmd->std_in = std_in;
	cmd->std_out = std_out;
	cmd->is_separated = is_separated;
	cmd->is_bin = is_bin;
	return (cmd);
}

void print_cmds(t_list *cmd_list)
{
	t_cmd *cmd;
	t_arg *arg;
	while(cmd_list)
	{
		cmd = cmd_list->content;
		arg = cmd->args->content;
		printf("printf = %d\n\n", printf("name = %s\nflags = %s\narg_name = %s\narg_is_env = %d\n", cmd->name, cmd->flags, arg->name, arg->is_env));
		cmd_list = cmd_list->next;
	}
}

void	example(t_info *info)
{
	t_cmd	*cmd;

	cmd = new_cmd(ft_strdup("echo"), ft_strdup("-n"), NULL, -1, 1, 0, 0);
	info->cmd = ft_lstnew(cmd);
	cmd = new_cmd(ft_strdup("sdfsf"), ft_strdup("sadf"), NULL, -1, 1, 0, 0);
	ft_lstadd_back(&(info->cmd), ft_lstnew(cmd));
	cmd = new_cmd(ft_strdup("echo"), ft_strdup(""), NULL, -1, 1, 0, 0);
	ft_lstadd_back(&(info->cmd), ft_lstnew(cmd));
	print_cmds(info->cmd);
}
int			strl(char *str)
{
	char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		s++;
	return (s - str);
}

char		*strj(char *s1, char s2)
{
	unsigned int	i;
	char			*out_str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	if (!(out_str = malloc(sizeof(char) * (strl(s1) + 2))))
		return (NULL);
	while (s1[++i])
		out_str[i] = s1[i];
	free(s1);
	out_str[i++] = s2;
	out_str[i] = '\0';
	return (out_str);
}

int cmd_count(char *cmd)
{
	int i;
	int j;
	int cnt;
	char *str;
	int len;

	len = strl(cmd);
	cnt = 0;
	str = malloc(sizeof(char) * 1);
	*str = '\0';
	i = -1;

	while (cmd[++i])
	{
		if (len >= i + 1)
		{
			if ((cmd[i] == ' ' || cmd[i] == 34 || cmd[i] == 39) && cmd[i + 1] == 39)
			{
				i += 2;
				while (cmd[i] != 39 && i < len)
				{
					str = strj(str, cmd[i++]);
				}
				printf("\t\t\t\t|%s|\n", str);
				free(str);
				if (cmd[i + 1] == ' ')
					printf("\t\t\t\t| |\n");
				str = malloc(sizeof(char) * 1);
				*str = '\0'; 
				if (i == len)
					return (-1);
				cnt++;
				i++;
			}
			if ((cmd[i] == ' ' || cmd[i] == 34 || cmd[i] == 39) && cmd[i + 1] == 34)
			{
				i += 2;
				while (cmd[i] != 34 && i < len)
				{
					str = strj(str, cmd[i++]);
				}
				printf("\t\t\t\t|%s|\n", str);
				free(str);
				if (cmd[i] == ' ')
					printf("\t\t\t\t| |\n");
				str = malloc(sizeof(char) * 1);
				*str = '\0'; 
				if (i == len)
					return (-1);
				cnt++;
				i++;
				printf("%c\n", cmd[i]);
			}
			
			if ((cmd[i] == ' ' || i == 0 || cmd[i] == 39 || cmd[i] == 34) && cmd[i + 1] != ' ' && cmd[i] != 34 && cmd[i] != 39)
			{
				if (cmd[i] == ' ') 
					i++;
				// printf("%d\n", i);
				while (cmd[i] != ' ' && cmd[i] && cmd[i] != 34 && cmd[i] != 39)
					str = strj(str, cmd[i++]);
				// printf("%d\n", i);
				printf("\t\t\t\t|%s|\n", str);
				free(str);
				if (cmd[i] == ' ')
					printf("\t\t\t\t| |\n");
				str = malloc(sizeof(char) * 1);
				*str = '\0';
				cnt++;
				i--;
			}
		}
	}
	return (cnt);
}

void	parser(char *command)
{
	int cmnd;

	if (!command)
		return ;
	printf("count = %d\n" , cmd_count(command));

}

int main(int argc, char **argv, char *envp[])
{
	t_info info;
	example(&info);


	parser("echo this is the first example     \"hello world\"'ABC'     sljfd");
	
	
	return (0);
}
