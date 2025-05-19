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
Exit_status depands of multiple things,
If the commande work, 0
If a commande exist and fail cause of the arg, 1
If a commande exist and you dont have the permission 126
If a commande doesn't exist 127
If a signal Kill or interrupte the commande 127 + signal
If error parsing 2
Exit status come with Error message in your terminal,
	don't forget that the error fd is 2
(putstr_fd)
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

static int	get_current_directory(char *buf, size_t size)
{
	if (!getcwd(buf, size))
	{
		perror("cd: get cwd");
		return (0);
	}
	return (1);
}

// TOO LONG
static char	*get_cd_target(char **input, t_env_vars *env_list)
{
	char	*target;

	if (input[1] && input[2])
	{
		write(2, "cd: too many arguments\n", 24);
		return (NULL);
	}
	if (!input[1])
	{
		target = get_env_value(env_list, "HOME");
		if (!target)
		{
			perror("cd: HOME not set");
			return (NULL);
		}
	}
	else if (strcmp(input[1], "-") == 0)
	{
		target = get_env_value(env_list, "OLDPWD");
		if (!target)
		{
			perror("cd: OLDPWD not set");
			return (NULL);
		}
		printf("%s\n", target);
	}
	else
		target = input[1];
	return (target);
}

int	ft_cd(char **input, t_env_vars **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*target;

	target = get_cd_target(input, *env_list);
	if (!target)
		return (1);
	if (!get_current_directory(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	if (!get_current_directory(new_pwd, sizeof(new_pwd)))
		return (1);
     update_env_var(env_list, "OLDPWD", old_pwd);
     update_env_var(env_list, "PWD", new_pwd);
	return (0);
}

// TOO LONG
// ECHO // Print failure (rare) 2
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
		if (printf("%s", args[i]) < 0)
		{
			perror("echo: write error");
			return (2);
		}
		if (args[i + 1] && printf(" ") < 0)
		{
			perror("echo: write error");
			return (2);
		}
		i++;
	}
	if (newline && printf("\n") < 0)
	{
		perror("echo: write error");
		return (2);
	}
	return (0);
}

// ENV
// empty list is not an error
// only read only so just did single ptr
int	env(t_env_vars *head)
{
	if (!head)
	{
		perror("env: no environment list");
		return (1);
	}
	while (head)
	{
		if (head->key && head->value)
		{
			if (printf("%s=%s\n", head->key, head->value) < 0)
			{
				perror("env: write error");
				return (2);
			}
		}
		head = head->next;
	}
	return (0);
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

// void	print_arg_error(const char *arg)
// {
// 	write(STDERR_FILENO, "minishell: exit: ", 17);
// 	write(STDERR_FILENO, arg, strlen(arg));
// 	write(STDERR_FILENO, ": numeric argument required\n", 28);
// }

// void	print_too_many_args(void)
// {
// 	write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
// }

// void	print_error(const char *prefix, const char *msg)
// {
// 	write(STDERR_FILENO, prefix, strlen(prefix));
// 	write(STDERR_FILENO, msg, strlen(msg));
// }

// EXIT we are feeding a double ptr so hence no addrss
/*
Input			Behavior	Exit Code
exit			exits		 0
exit 42			exits		 42
exit 256    exits			0
exit -1			exits		 255
exit 42     abc	prints error, doesn't exit	1
exit abc	prints error, exits	2
*/
// REPLACE ATOI WITH FT_ATOI
int	exit_shell(char **args, t_env_vars **env_list)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (!args[1])
	{
		clean_env_lst(env_list);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		perror("exit: numeric argument required");
		clean_env_lst(env_list);
		exit(2);
	}
	if (args[2])
	{
		perror("exit: too many arguments");
		return (1);
	}
	exit_code = atoi(args[1]) % 256;
	clean_env_lst(env_list);
	exit(exit_code);
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
//ADDD REAL ONES FUNCTIONS OF STRDUP AND STRCMP
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

void	update_env_var(t_env_vars **env_list, const char *key, const char *value)
{
    t_env_vars * var = get_env_node(*env_list, key);
    if (var && var->value && ft_strcmp(var->value, "") != 0)
    {
        free(var->value);
        var->value = ft_strdup(value);
    }
 
}
// kk no bash returns empty so need to add empty string still stores value
// Start with a digit
// Contain invalid characters (like !, @, -, etc.)
// Are empty
static int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// replace = with null to turn into key value
// just for norm
static void	print_invalid_identifier_error(const char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, strlen(arg));
	write(2, "`: not a valid identifier\n", 27);
}

static int	handle_export_arg(t_env_vars **env_list, char *arg)
{
	char	*equal_sign;
	char	*temp;

	temp = ft_strdup(arg);
	if (!temp)
	{
		perror("export: strdup");
		return (1);
	}
	equal_sign = ft_strchr(temp, '=');
	if (!is_valid_identifier(temp))
	{
		print_invalid_identifier_error(arg);
		free(temp);
		return (1);
	}
	if (equal_sign)
	{
		*equal_sign = '\0';
		set_env_var(env_list, temp, equal_sign + 1);
	}
	else
		set_env_var(env_list, temp, "");
	free(temp);
	return (0);
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

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("pwd:get cwd failed");
		return (1);
	}
	else
	{
		if (printf("%s\n", pwd) < 0)
		{
			perror("pwd: write error");
			return (2);
		}
	}
	return (0);
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

//BAD ADVICE GRRRRRR
// void ensure_minimal_vars(t_env_vars **env)
// {
// 	char buf[PATH_MAX];

// 	if (!get_env_value(*env, "PWD") && getcwd(buf, sizeof(buf)))
// 		set_env_var(env, "PWD", buf);

// 	if (!get_env_value(*env, "SHLVL"))
// 		set_env_var(env, "SHLVL", "1");

// 	if (!get_env_value(*env, "PATH"))
// 		set_env_var(env, "PATH", "/usr/bin:/bin");

// 	if (!get_env_value(*env, "HOME"))
// 		set_env_var(env, "HOME", "/");  
// }

int	ft_unset(t_env_vars **head, char *key)
{
	t_env_vars	*node;

	if (!head || !key || *key == '\0')
		return (1);
	node = extract_node(head, key);
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
	return (0);  // even if it's PWD or HOME — allow it
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
