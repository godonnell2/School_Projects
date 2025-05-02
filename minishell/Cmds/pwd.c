#include "minishell.h"
#include <unistd.h>

// print working directory
void	ft_pwd(void)
{
	char	pwd[100000];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd:get cwd failed");
		last_exit_code = 1;
		return ;
	}
	else
	{
		printf("%s\n", pwd);
		last_exit_code = 0;
	}
}
