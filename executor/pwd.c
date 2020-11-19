#include "executor.h"

char *pwd(t_cmd *cmd, t_list *args, t_list *env_list)
{
	char *pwd;
	
	if (!(getcwd(pwd, 228)))
		return (NULL);
	return (pwd);
}