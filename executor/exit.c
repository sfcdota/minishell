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

int exit_(t_list *arg_list, t_list *env_list)
{
	t_arg *arg;
	char *code;
	long long int kek;
	int is_neg;
	
	is_neg = 0;
	ft_putendl_fd("exit", 1);
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
			is_neg = 1;
		kek = ft_atoi(code);
		if ((is_neg && !kek) || (!is_neg && kek == -1))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(code, 1);
			ft_putendl_fd(": numeric argument required", 1);
			return (1);
		}
		return (kek % 256);
	}
	return (0);
}