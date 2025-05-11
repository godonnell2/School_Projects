#include "minishell.h"

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
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

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
	if (!s)
		return (NULL);
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

void initialize_env_list(t_env_vars **env_list)
{
    extern char **environ;
    int i = 0;
    char *env_var;
    char *equal_sign;

    while ((env_var = environ[i]))
    {
        equal_sign = strchr(env_var, '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            set_env_var(env_list, env_var, equal_sign + 1);
            *equal_sign = '=';
        }
        i++;
    }
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
        //ERROR CHECK???
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
			return (NULL);
		}
		target_path = home->value;
	}
	return (target_path);
}

int	ft_cd(char *input, t_env_vars **env_list)
{
	char	old_pwd[10000];
	char	new_pwd[10000];
	char	*target_path;

	target_path = get_target_path(input, env_list);
	if (!get_current_directory(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(target_path) == -1)
	{
		perror("cd: did not find target path ie no such dir");
		return (1);
	}
	if (!get_current_directory(new_pwd, sizeof(new_pwd)))
		return (1);
	set_env_var(env_list, "OLDPWD", old_pwd);
	set_env_var(env_list, "PWD", new_pwd);
	return (0);
}

// ECHO
int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

// ENV

int	env(t_env_vars *head)
{
	if (!head)
	{
		return (1);
	}
	while (head)
	{
		if (head->key && head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}

// EXIT
int	exit_shell(t_env_vars **env_list)
{
	printf("exit\n");
	free_env_vars(*env_list);
	return (0);
}
// so if we have a signal we want to return 1 or some other number

// EXPORT
/*
The export command in Unix/Linux shells is used to set environment variables,
making them available to child processes of the current shell session.

Current Shell Only: By default, variables are local to the current shell.
export makes them available to subprocesses (like scripts or commands you run).

*/
/*
handle case sensitivity this is correct right as bash treats them separately
do i need to check validity of export key words??
plus need to handle malloc fail in strdup right now im just losing the var!!!!

nheritance: When a process creates a child process (using fork),
	the child process inherits a copy of the parent's environment. However,
	by default,
	not all variables from the parent process are passed to the child.
 Only the variables that have been explicitly "exported" are included.
 // NEED TO REMEMBER TO FREE
*/

int ft_export(t_env_vars **env_list, char **args)
{
    int i;
    char *equal_sign;

    if (!args[1]) 
    {
        // Print all exported variables
        return (0);
    }

    i = 1;
    while (args[i])
    {
        equal_sign = strchr(args[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            set_env_var(env_list, args[i], equal_sign + 1);
            *equal_sign = '='; // Restore original string
        }
        i++;
    }
    return (0);
}
// print working directory
int	ft_pwd(void)
{
	char	pwd[100000];
	int		exit_code;

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd:get cwd failed");
		return (exit_code = 1);
	}
	else
	{
		printf("%s\n", pwd);
		return (exit_code = 0);
	}
}

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

int	ft_unset(t_env_vars **head, char *key)
{
	t_env_vars	*node_to_remove;

	if (!head || !key)
	{
		return (1);
	}
	node_to_remove = extract_node(head, key);
	if (node_to_remove)
	{
		free(node_to_remove->key);
		free(node_to_remove->value);
		free(node_to_remove);
		return (0);
	}
	else
	{
		return (0);
	}
}
// Note: Typically unset returns success even if var didn't exist
// hence the else

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
