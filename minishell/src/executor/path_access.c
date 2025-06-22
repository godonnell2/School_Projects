#include "minishell.h"
#include <sys/stat.h>

char	*get_path_variable(t_env_vars *env_vars)
{
	t_env_vars	*current;

	current = env_vars;
	//printf("IN GET_PATH_VAR Checking env var: %s=%s\n", env_vars->key,
			//env_vars->value); // DEBUG
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", 5) == 0)
		{
			DEBUG_LOG("IN_GET_PATH _VARFound PATH: %s\n", env_vars->value);
			// Debugging
			return (current->value);
		}
		current = current->next;
	}
	DEBUG_LOG("INGETPATHVAR: PATH variable not found.\n"); // Debugging
	return (NULL);
}

void	check_command_in_path(char **path_arr, char *cmd, char *full_path)
{
	size_t	p_len;
	size_t	c_len;
	char	**temp_patharr;
 DEBUG_LOG("[check_command_in_path] Searching command '%s' in PATH dirs\n", cmd);
	temp_patharr = path_arr;
	while (*temp_patharr != NULL)
	{
		p_len = ft_wordlen(*temp_patharr);
		c_len = ft_wordlen(cmd);
		if ((p_len + c_len + 2) > PATH_MAX)
			return ;
		cat_strs_char(full_path, *temp_patharr, '/', cmd);
		DEBUG_LOG("[check_command_in_path] Trying: %s\n", full_path);
		DEBUG_LOG("Resolved path: %s\n", full_path); // Debugging
		if (access(full_path, X_OK) == 0)
			return ;
		temp_patharr++;
	}
	full_path[0] = '\0';
}


int is_directory(const char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

/// usr/bin:/bin
// Treat as path if contains slash
// Otherwise search in PATH

void resolve_command_full_path(t_shell *shell, char *cmd, char *full_path)
{
    char buff[SPLIT_BUFF_SIZE];
    char **path_arr;
    char *path_env;

    DEBUG_LOG("[resolve_command_full_path] Resolving command: '%s'\n", cmd);

    full_path[0] = '\0';

    if (ft_strchr(cmd, '/'))
    {
        DEBUG_LOG("[resolve_command_full_path] Command contains '/'\n");

        if (access(cmd, F_OK) != 0)
        {
            DEBUG_LOG("[resolve_command_full_path] %s: F_OK failed\n", cmd);
            shell->last_exit_code = 127;
            return;
        }

        if (is_directory(cmd))
        {
            DEBUG_LOG("[resolve_command_full_path] %s: is a directory\n", cmd);
            shell->last_exit_code = 126;
            return;
        }

        
        ft_strcpy(cmd, full_path);
        DEBUG_LOG("[resolve_command_full_path] Using direct path: %s\n", full_path);
        return;
    }//my strcpy is reversed

    path_env = get_path_variable(shell->env_vars);
    if (!path_env)
    {
        DEBUG_LOG("[resolve_command_full_path] PATH env variable missing\n");
        shell->last_exit_code = 127;
        return;
    }

    DEBUG_LOG("[resolve_command_full_path] PATH env: %s\n", path_env);

    path_arr = ft_split_buff(path_env, ':', buff);
    check_command_in_path(path_arr, cmd, full_path);

    if (full_path[0] == '\0')
    {
        DEBUG_LOG("[resolve_command_full_path] Could not resolve command '%s'\n", cmd);
        shell->last_exit_code = 127;
    }
    else
    {
        DEBUG_LOG("[resolve_command_full_path] Resolved command path: %s\n", full_path);
    }
}

void resolve_all_command_paths(t_shell *shell, t_command *cmds)
{
    char full_path[PATH_MAX];
    int builtin;
    t_command *curr = cmds;

    DEBUG_LOG("[resolve_all_command_paths] Starting path resolution for command list\n");

    while (curr)
    {
        if (!curr->args || !curr->args[0])
        {
            DEBUG_LOG("[resolve_all_command_paths] Skipping command with NULL or empty args\n");
            curr = curr->next;
            continue;
        }

        DEBUG_LOG("[resolve_all_command_paths] Checking command: '%s'\n", curr->args[0]);

        builtin = is_built_in(curr);
        if (!builtin)
        {
            resolve_command_full_path(shell, curr->args[0], full_path);

            if (full_path[0] != '\0')
            {
                curr->full_path = ft_strdup(full_path);
                if (!curr->full_path)
                {
                    perror("ft_strdup");
                    curr->full_path = NULL;
                }
                else
                {
                    DEBUG_LOG("[resolve_all_command_paths] Command full_path set to: %s\n", curr->full_path);
                }
            }
            else
            {
                DEBUG_LOG("[resolve_all_command_paths] Empty full_path for command: %s\n", curr->args[0]);
            }
        }
        else
        {
            DEBUG_LOG("[resolve_all_command_paths] Command is builtin: %s\n", curr->args[0]);
            curr->full_path = NULL;
        }
        curr = curr->next;
    }
}