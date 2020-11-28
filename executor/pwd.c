#include "executor.h"

int pwd(t_cmd *cmd)
{
	char *pwd;
	
	if (!(pwd = getcwd(NULL, 228)))
		return(ret_with_msg(cmd->name, " : Internal error. Lib func getcwd got error.", NULL, 1));
	ft_putendl_fd(pwd, cmd->std_out);
	return (0);
}