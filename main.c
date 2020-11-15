#include "minishell.h"

int main()
{
	char *kek;
	kek = malloc(MAX_CMD_LENGTH);
	while(1)
	{
		if (write(1, "> ", 2) == -1 || read(0, kek, MAX_CMD_LENGTH) == -1)
			exit(-1);
		if (!ft_strncmp(kek, "exit\n", MAX_CMD_LENGTH))
			exit(0);
		//parsing
		//execution
		ft_memset(kek, 0, MAX_CMD_LENGTH);
	}
}