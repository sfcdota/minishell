#include "executor.h"

/*
** check for type == -1 made for default adding
** not default case: adding PWD and OLDPWD in cd, because in error we need free
*/

t_env	*add_env(t_list **env_list, char *key, char *value)
{
	t_env *env;
	
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->key = key;
	env->value = value;
	ft_lstadd_back(env_list, ft_lstnew(env));
	return (env);
}



void	sort_envs(t_list *env_list)
{
	t_list *begin;
	t_list *begin2;
	void	*temp;
	
	begin = env_list;
	while(begin)
	{
		begin2 = env_list;
		while(begin2->next)
		{
			if (ft_strcmp(((t_env *)(begin2->content))->key,
				((t_env *)(begin2->next->content))->key) > 0)
			{
				temp = begin2->content;
				begin2->content = begin2->next->content;
				begin2->next->content = temp;
			}
			begin2 = begin2->next;
		}
		begin = begin->next;
	}
}

char *to_delimiter(char *envp_string, char delimiter)
{
	while (*envp_string && *envp_string != delimiter)
		envp_string++;
	return envp_string;
}

char *get_substr(char *begin, char *end)
{
	char *out;
	
	if (!end)
		end = to_delimiter(begin, '\0');
	if (!begin || !(out = malloc(end - begin + 2)))
		return (NULL);
	ft_strlcpy(out, begin, end - begin + 1);
	return (out);
}

t_list	*envs_to_list(char *envp[])
{
	t_list *env_list;
	char *temp;
	
	env_list = NULL;
	while(*envp)
	{
		temp = to_delimiter(*envp, '=');
		add_env(&env_list, get_substr(*envp, temp),
		get_substr(temp ? temp + 1 : temp, NULL));
		envp++;
	}
	add_env(&env_list, ft_strdup("?"), ft_strdup("0"));
	if (!get_env_val_by_key("PWD", env_list))
	{
		if (!(temp = getcwd(NULL, 228)))
			str_replace(get_env_list_by_key("?", env_list)->content,
				ft_strdup("1"));
		else
			add_env(&env_list, ft_strdup("PWD"), temp);
	}
	sort_envs(env_list);
	return (env_list);
}

char *strappend(char **s1, char *s2)
{
	char *temp;
	
	temp = ft_strjoin(*s1, s2);
	clear_ptr((void **)s1);
	*s1 = temp;
}

char	**env_list_to_array(t_list *env_list)
{
	int i;
	int j;
	char **out;
	
	i = ft_lstsize(env_list);
	if(!(out = ft_calloc(sizeof(char *), i + 1)))
		return (NULL);
	j = -1;
	while (++j < i)
	{
		strappend(&out[j], ((t_env *)env_list->content)->key);
		strappend(&out[j], "=");
		strappend(&out[j],  ((t_env *)env_list->content)->value);
		env_list = env_list->next;
	}
	return (out);
}

void	print_env_array(char **envp)
{
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
}

void	ft_lst_elem_delete(t_list **lst, t_list *elem, void (*del)(void *))
{
	if (lst && *lst)
	{
		if (*lst == elem)
		{
			*lst = (*lst)->next;
			if (del)
				del(elem->content);
			free(elem);
		}
		else
		{
			while (*lst && (*lst)->next != elem)
				*lst = (*lst)->next;
			if ((*lst)->next == elem)
			{
				(*lst)->next = elem->next;
				if (del)
					del(elem->content);
				free(elem);
			}
		}
	}
}