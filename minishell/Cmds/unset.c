#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Deletes shell/environment variables so they no longer exist.
Affects Current Shell Only
Changes are not inherited by child processes (unlike export).
Works on Functions Too
Can also remove shell functions:
No Effect on Read-Only Variables
Fails silently (or with an error) if the variable is marked readonly.

Command	Description
unset VAR	Removes the variable VAR.

*/

static t_env_vars	*extract_node(t_env_vars **head, char *key)
{
	t_env_vars	*curr;
	t_env_vars	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			return (curr);
		}
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

void	ft_unset(t_env_vars **head, char *key)
{
	t_env_vars	*node_to_remove;

	if (!head || !key)
	{
		last_exit_code = 1;
		return ;
	}
	node_to_remove = extract_node(head, key);
	if (node_to_remove)
	{
		free(node_to_remove->key);
		free(node_to_remove->value);
		free(node_to_remove);
		last_exit_code = 0;
	}
	else
	{
		last_exit_code = 0;
	}
}
// Note: Typically unset returns success even if var didn't exist
// hence the else