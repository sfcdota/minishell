#include "executor.h"

int is_str_numeric(char *s)
{
	if (*s == '-')
		s++;
	while (s && *s)
		if (!ft_isdigit(*s))
			return (0);
	return (1);
}

int exit_(t_list *arg_list, t_list *env_list, t_info *info)
{
	t_arg *arg;
	char *code;
	long long int kek;
	int is_neg;
	
	is_neg = 0;
	if (arg_list->next)
	{
		ft_putendl_fd("exit: too many arguments", 1);
		return (1);
	}
	if (arg_list)
	{
		arg = ((t_arg *) (arg_list->content));
		code = arg->is_env ? get_env_val_by_key(arg->name, env_list)
			: arg->name;
		if (*code == '-')
		{
			if (is_str_numeric(code + 1))
				is_neg = 1;
			else
				return (1);//need error msg num arg required
		}
		else if (is_str_numeric(code))
			return (1); //also need error msg
		kek = ft_atoi(code);
		if ((is_neg && !kek) || (!is_neg && kek == -1))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(code, 1);
			ft_putendl_fd(": numeric argument required", 1);
			return (1);
		}
		ft_exit("exit", kek % 256, info);
	}
	return (0);
}