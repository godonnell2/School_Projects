#include "minishell.h"

// e have to update the path name before the semicolon??
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

Built-in commands (e.g., cd, export, exit,
	source) are part of the shell's own code.
 They run in the current shell's process,
	so they directly modify the shell's state
 (environment variables, CWD, etc.).

External commands (e.g., /bin/ls, python) spawn a subprocess (child shell).
Changes they make (e.g., export VAR=value in a script) are confined to the
child process and lost when it exits.

No Subprocess Overhead: Built-ins avoid spawning a new process,
	making them faster.

Persistent Changes: Their effects are visible in the parent shell
 after execution.

Control Flow: Built-ins like exit, return,
	or source must run in the parent shell to terminate the session or modify
	its state.
*/

/*
enviro vars are key-value pairs that a process inherits from its parent.
These are used to pass configuration information.
extern means it's held in an external file or lib  <unistd.h>
*/

// if (input[i] == '\0' || input[i] == '~' || input[i] == '-')
// chdir interprets it relative to the curr dir so works for both rel/abs

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

// EXIT we are feeding a double ptr so hence no addrss
/*
Input			Behavior	Exit Code
exit			exits			0
exit 42			exits			42
exit 256    exits			0
exit -1			exits			255
exit 42     abc	prints error, doesn't exit	1
exit abc	prints error, exits	2
*/
// REPLACE ATOI WITH FT_ATOI

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
// ADDD REAL ONES FUNCTIONS OF STRDUP AND STRCMP
void	set_env_var(t_env_vars **env_list, const char *key, const char *value)
{
	t_env_vars	*current;
	t_env_vars	*new_node;

	current = *env_list;
   while (current) {
        if (ft_strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = ft_strdup(value);
			{ 
				perror("minishell: export: memory allocation failed for value");
            	return;
			}
        }
        current = current->next;
    }


    new_node = malloc(sizeof(t_env_vars));
    if (!new_node) {
        perror("malloc failed in set_env_var");
        return;
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    
    if (*env_list == NULL) {
        *env_list = new_node;
    } else {
        t_env_vars *tail = *env_list;
        while (tail->next) tail = tail->next;
        tail->next = new_node;
    }
}

// replace = with null to turn into key value
// just for norm
//Var names  in bash must start with a letter or an underscore,
// followed by letters, numbers, or underscores.
/*The bottom block handles export ARG without =
because without a value will create empty string
havent included the attempted var name in fail msg maybe include?
*/

int	handle_export_arg(t_env_vars **env_list, char *arg)
{
	char	*equal_sign;
	char	*name;
	int		result;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		name = ft_substr(arg, 0, equal_sign - arg);
		if (!name)
		{
			perror("export: substr");
			return (1);
		}
		result = is_valid_identifier_var(name);
		DEBUG_PRINTF("[DEBUG] is_valid_identifier_var('%s') = %d\n", name, result); //debufg
		
		if (!result)
		{
			write(2, "not a valid identifier\n", 23);
			return (1);
		}
		set_env_var(env_list, name, equal_sign + 1);
		free(name);
	}
	else
	{
		if (!is_valid_identifier_var(arg))
		{
			write(2, "not a valid identifier\n", 23);
			return (1);
		}
		set_env_var(env_list, arg, "");
	}
	return (0);
}



/*
ash Behavior: If you run export A=1 B- C=3, bash will try to process all arguments. 
It will report an error for B- but will still attempt to set A=1 and C=3. 
The overall export command will return 1 if any argument failed. 
It does not stop at the first error.
*/
int	ft_export(t_env_vars **env_list, char **args)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (!args[1])
	{
			DEBUG_PRINTF("[DEBUG] No arguments provided to export.\n");
			print_env_vars(*env_list);
		return 0;
	}
	DEBUG_PRINTF("[DEBUG] Starting export ofarguments\n");
	i = 1;
	
	while (args[i] )
	{
		DEBUG_PRINTF( "[DEBUG] Processing arg\n");
		 if (handle_export_arg(env_list, args[i]) != 0)
		 {
			DEBUG_PRINTF("[DEBUG] Invalid identifier detected. Returning early with exit code 1.\n");
			exit_code = 1;
			DEBUG_PRINTF("in incorrect var exit_code =%d\n", exit_code);
		 }
		i++;
	}
	DEBUG_PRINTF("exiting fucntion in incorrect var exitcode=%d=\n", exit_code);
	return (exit_code);
	
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
