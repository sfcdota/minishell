#include "executor.h"

void sighandler(int signum)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	if (signum == SIGINT)
	{
		
	}
}

/*
 * 
 * SIGQUIT perform a core dump, means, in must be killed by kill(,) func
 * which automatically make core dump on child process
 * 
 */