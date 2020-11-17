#include "executor.h"

int	add_var(t_list *env_list, char *key, char *value, int is_hidden)
{
	t_env *env;
	
	if (!(env = malloc(sizeof(t_env))))
		return (-1);
	env->key = key;
	env->value = value;
	env->is_hidden = is_hidden;
	ft_lstadd_back(&env_list, ft_lstnew(env));
	return (0);
}