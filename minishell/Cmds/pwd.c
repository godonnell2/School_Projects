#include "minishell.h"

#include <unistd.h>

// print working directory
void	ft_pwd(void)
{
	char	pwd[100000];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd:get cwd in pwd");
		return ;
	}
	else
	{
		printf("%s\n", pwd);
	}
}
