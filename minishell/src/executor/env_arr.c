#include "minishell.h"

static char	*create_env_string(char *key, char *value)
{
	int		len_key;
	char	*env_str;
	int		len_total;

	len_key = ft_wordlen(key);
	len_total = len_key + ft_strlen(value) + 2;
	env_str = malloc(len_total);
	if (!env_str)
		return (NULL);
	ft_strcpy(key, env_str);
	env_str[len_key] = '=';
	ft_strcpy(value, env_str + len_key + 1);
	return (env_str);
}

// IS FREEING CORECT ???
// printf("ENV: %s=%s\n", curr->key, curr->value);

static int	populate_env_array(char **env_arr, t_env_vars *curr)
{
	int	i;

	i = 0;
	while (curr)
	{
		env_arr[i] = create_env_string(curr->key, curr->value);
		if (!env_arr[i])
		{
			while (--i >= 0)
				free(env_arr[i]);
			return (0);
		}
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (1);
}

char	**convert_env_to_array(t_env_vars *env_vars)
{
	int		count;
	char	**env_arr;

	count = count_env_nodes(env_vars);
	env_arr = malloc(sizeof(char *) * (count + 1));
	if (!env_arr)
		return (NULL);
	if (!populate_env_array(env_arr, env_vars))
	{
		free(env_arr);
		return (NULL);
	}
	return (env_arr);
}

void	free_env_array(char **env_array)
{
	char	**tmp;

	if (!env_array)
		return ;
	tmp = env_array;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(env_array);
}
