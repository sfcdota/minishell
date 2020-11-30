#include "executor.h"

int		abs(int n)
{
	return (n < 0 ? - n : n);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	if ((!s1 && !s2))
		return (0);
	while ( *s1 == *s2 && (*s1 != '\0' || *s2 != '\0'))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char *get_env_val_by_key(char *key, t_list *env_list)
{
	t_env *env;

	while(key && env_list)
	{
		env = (t_env *)(env_list->content);
		if(!ft_strcmp(key, env->key))
			return env->value;
		env_list = env_list->next;
	}
	return (NULL);
}

t_env *get_env_by_key(char *key, t_list *env_list)
{
	t_env *env;
	
	while(env_list)
	{
		env = (t_env *)(env_list->content);
		if(!ft_strcmp(key, env->key))
			return (env);
		env_list = env_list->next;
	}
	return (NULL);
}

t_list *get_env_list_by_key(char *key, t_list *env_list)
{
	while(env_list)
	{
		if(!ft_strcmp(key, ((t_env *)(env_list->content))->key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}