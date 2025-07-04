#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

// do we have to update the path name before the semicolon??
/*
Symbolic Links (Symlinks): Unlike hard links, symlinks are independent files
that store a pointer to the target. They can cross filesystems and can
reference directories.
A symlink is a file that contains a path (either relative or absolute)
to another file or directory. When you access the symlink,
the operating system automatically redirects you to the target file or
directory.
t’s similar to a shortcut in Windows, but at the filesystem level.

*/

// do we need all space chars??
int	skip_cd_cmd(const char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == 'c' && input[i + 1] == 'd' && (input[i + 2] == '\0'
			|| input[i + 2] == ' ' || input[i + 2] == '\t'))
	{
		i += 2;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

t_env_vars	*get_env_node(t_env_vars *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	const char	*p = s;
	char		*dup;
	size_t		i;

	i = 0;
	len = 0;
	while (*p++)
	{
		len++;
	}
	dup = malloc(len + 1);
	if (!dup)
	{
		return (NULL);
	}
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

void	set_env_var(t_env_vars **head, const char *key, const char *value)
{
	t_env_vars	*node;

	node = get_env_node(*head, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		node = malloc(sizeof(t_env_vars));
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->next = *head;
		*head = node;
	}
}

// if (input[i] == '\0' || input[i] == '~' || input[i] == '-')
// chdir interprets it relative to the curr dir so works for both rel/abs
int	get_current_directory(char *buffer, size_t size)
{
	if (!getcwd(buffer, size))
	{
		perror("cd: getcwd failed");
		last_exit_code = 1;
		return (0);
	}
	return (1);
}

char	*get_target_path(char *input, t_env_vars **env_list)
{
	int			i;
	char		*target_path;
	t_env_vars	*home;

	i = skip_cd_cmd(input);
	target_path = input + i;
	while (*target_path == ' ' || *target_path == '\t')
	{
		target_path++;
	}
	if (*target_path == '\0')
	{
		home = get_env_node(*env_list, "HOME");
		if (!home || !home->value)
		{
			perror("cd: HOME not set");
			last_exit_code = 1;
			return (NULL);
		}
		target_path = home->value;
	}
	return (target_path);
}

void	ft_cd(char *input, t_env_vars **env_list)
{
	char	old_pwd[10000];
	char	new_pwd[10000];
	char	*target_path;

	target_path = get_target_path(input, *env_list);
	if (!get_current_directory(old_pwd, sizeof(old_pwd)))
		return ;
	if (chdir(target_path) == -1)
	{
		perror("cd: did not find target path ie no such dir");
		last_exit_code = 1;
		return ;
	}
	if (!get_current_directory(new_pwd, sizeof(new_pwd)))
		return ;
	set_env_var(env_list, "OLDPWD", old_pwd);
	set_env_var(env_list, "PWD", new_pwd);
	last_exit_code = 0;
}
