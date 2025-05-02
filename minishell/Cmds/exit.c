#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_shell(t_env_vars **env_list)
{
	printf("exit\n");
	free_env_list(env_list);
	exit(0);
}
