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

/*
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
*/

/*
enviro vars are key-value pairs that a process inherits from its parent. 
These are used to pass configuration information.
extern means it's held in an external file or lib  <unistd.h> 
*/
void	initialize_env_list(t_env_vars **env_list)
{
	extern char	**environ;
	int			i;
	char		*env_var;
	char		*equal_sign;

	i = 0;
	while (environ[i] != NULL)
	{
		env_var = environ[i];
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
// if (input[i] == '\0' || input[i] == '~' || input[i] == '-')
// chdir interprets it relative to the curr dir so works for both rel/abs

// do we need all space chars no that's ºarser job??

static int	get_current_directory(char *buf, size_t size)
{
	if (!getcwd(buf, size))
	{
		perror("cd: get cwd");
		return (0);
	}
	return (1);
}

int	ft_cd(char **input, t_env_vars **env_list)
{
	char	old_pwd[10000];
	char	new_pwd[10000];

	if (!input[1])
	{
		perror("cd: missing argument");
		return (1);
	}
	if (!get_current_directory(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(input[1]) != 0)
	{
		perror("failure to chdir in cd");
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
//empty list is not an error 
// only read only so just did single ptr
int	env(t_env_vars *head)
{
	if (!head)
	{
		return (0);
	}
	while (head)
	{
		if (head->key && head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}


void clean_env_lst(t_env_vars **env_vars)
{
    t_env_vars *current = *env_vars;
    while (current != NULL) 
	{
        t_env_vars *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}
// EXIT we are feeding a double ptr so hence no addrss
int	exit_shell(t_env_vars **env_list)
{
	printf("exit\n");
	clean_env_lst(env_list);
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
void	set_env_var(t_env_vars **env_list, const char *key, const char *value)
{
	t_env_vars	*current;
	t_env_vars	*new_node;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env_vars));
	if (!new_node)
	{
		perror("malloc failed in set_env_var");
		return ;
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env_list;
	*env_list = new_node;
}

// when no equal sign is found we set the key with empty value
// is this what bash does
// kk no bash returns empty so need to add empty string still stores value
// NOT USING MY STRCHR I DONT KNOW WHY 
static int	handle_export_arg(t_env_vars **env_list, char *arg)
{
	char	*equal_sign;
	char	*temp;
	int		result;

	temp = ft_strdup(arg);
	if (!temp)
	{
		perror("export: ft_strdup");
		return (1);
	}
	equal_sign = strchr(temp, '=');
	result = 0;
	if (equal_sign)
	{
		*equal_sign = '\0';
		set_env_var(env_list, temp, equal_sign + 1);
	}
	else
	{
		set_env_var(env_list, temp, "");
	}
	free(temp);
	return (result);
}

int	ft_export(t_env_vars **env_list, char **args)
{
	int	i;
	int	status;

	if (!args[1])
		return (0);
	status = 0;
	i = 1;
	while (args[i] && status == 0)
	{
		status = handle_export_arg(env_list, args[i]);
		i++;
	}
	return (status);
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
	printf("Attempting to unset key: %s\n", key);
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
