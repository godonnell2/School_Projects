#include "minishell.h"
#include <unistd.h>

// print working directory
int	ft_pwd(void)
{
	char	pwd[100000];
	int exit_code; 

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd:get cwd failed");
		return exit_code = 1;
		
	}
	else
	{
		printf("%s\n", pwd);
		return exit_code = 0;
		
	}
}
