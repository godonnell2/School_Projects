#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	env(t_env_vars *head)
{
	if (!head)
	{
		
		return 1;
	}
	while (head)
	{
		if (head->key && head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	 return 0;
}
