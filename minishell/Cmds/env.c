#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	env(t_env_vars *head)
{
	while (head)
	{
		if (head->key && head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
