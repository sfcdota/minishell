#include "minishell.h"
#include "executor/executor.h"


  #include <stdio.h>

  
  void print_env(char **envp)
  {
	while(*envp)
	{
		ft_putstr_fd(*envp, 1);
		ft_putchar_fd('\n', 1);
		envp++;
	}
  }
int main(int argc, char **argv, char *envp[])
{
	char *kek;
//	*envp = ft_strdup("hui sosi");
//	free(envp[0]);
//	envp[0] = NULL;
//	print_env(envp);
//	printf("%s\n", envp[0]);
	kek = malloc(MAX_CMD_LENGTH);
	while(1)
	{
		if (write(1, "> ", 2) == -1 || read(0, kek, MAX_CMD_LENGTH) == -1)
			exit(-1);
		if (!ft_strncmp(kek, "exit\n", MAX_CMD_LENGTH))
			exit(0);
		else
		{
			print_env(envp);
			ft_putstr_fd("\n\n\n\n", 1);
			char *out = malloc(MAX_CMD_LENGTH);
			printf("chdir res = %d\n", chdir("./"));
			printf("getcwd res = %s\n", getcwd(out, MAX_CMD_LENGTH));
			print_env(envp);
			return (0);
		}
		//parsing
		//execution
		ft_memset(kek, 0, MAX_CMD_LENGTH);
	}
}