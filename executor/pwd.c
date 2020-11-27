#include "executor.h"

int pwd(t_cmd *cmd)
{
	char *pwd;
	
	pwd = NULL;
	if (!(getcwd(pwd, 228)))
		return(ret_with_msg("pwd : Internal error. Lib func getcwd got error.", 1));
	ft_putstr_fd(pwd, cmd->std_out);
	return (0);
}