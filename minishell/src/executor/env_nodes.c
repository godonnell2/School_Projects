
#include "minishell.h"

char	*get_env_value(t_env_vars *env_vars, const char *key)
{
	while (env_vars)
	{
		if (ft_strcmp(env_vars->key, key) == 0)
		{
			return (env_vars->value);
		}
		env_vars = env_vars->next;
	}
	return (NULL);
}

t_env_vars	*extract_node(t_env_vars **head, char *key)
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

int	count_env_nodes(t_env_vars *env_vars)
{
	int	count;

	count = 0;
	while (env_vars)
	{
		count++;
		env_vars = env_vars->next;
	}
	return (count);
}

void	update_env_var(t_env_vars **env_list, const char *key,
		const char *value)
{
	t_env_vars	*var;

	var = extract_node(env_list, (char *)key);
	if (var && var->value && ft_strcmp(var->value, "") != 0)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
}

void	clean_env_lst(t_env_vars **env_vars)
{
	t_env_vars	*current;
	t_env_vars	*next;

	current = *env_vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
