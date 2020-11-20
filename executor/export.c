#include "executor.h"

void print_env_list(t_list *env_list, char *prefix, int std_out)
{
	t_env *env;
	while (env_list)
	{
		env = (t_env *)(env_list->content);
		if (env->is_hidden != 1)
		{
			if (prefix)
				ft_putstr_fd(prefix, std_out);
			ft_putstr_fd(env->key, std_out);
			ft_putchar_fd('=', std_out);
			ft_putendl_fd(env->value, std_out);
		}
		env_list = env_list->next;
	}
}

int is_correct_var(char *s)
{
	if (ft_isdigit(*s))
		return (0);
	while (*s && *s != '=')
	{
		if (!(ft_isalnum(*s) || *s == '_'))
			return (0);
		s++;
	}
	return (1);
}

int export(t_cmd *cmd, t_list *arg_list, t_list *env_list)
{
	t_arg *arg;
	char *var_str;
	char *temp;
	
	if (arg_list)
	{
		arg = (t_arg *)(arg_list->content);
		var_str = arg->is_env ? get_env_val_by_key(arg->name, env_list) : arg->name;
		if (is_correct_var(var_str))
		{
			temp = to_delimiter(var_str, '=');
			add_env(&env_list, get_substr(var_str, temp),
		get_substr(temp ? temp + 1 : temp, NULL), -1);
		}
		else
			return (1);//var is not correct
	}
	print_env_list(env_list, "declare -x ", cmd->std_out);
	return (0);
}