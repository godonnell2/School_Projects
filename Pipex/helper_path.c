/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:11:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/04 21:04:44 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			printf("finding path\n");
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*check_command_in_path(char **path_arr, char *cmd)
{
	char	*full_cmd_path;
	size_t	p_len;
	size_t	c_len;
	char	**temp;

	temp = path_arr;
	while (*temp != NULL)
	{
		p_len = ft_wordlen(*temp);
		c_len = ft_wordlen(cmd);
		full_cmd_path = (char *)malloc(sizeof(char) * (p_len + c_len + 2));
		if (!full_cmd_path)
			return (NULL);
		cat_strs_char(full_cmd_path, *temp, '/', cmd);
		if (access(full_cmd_path, F_OK) == 0)
			return (full_cmd_path);
		free(full_cmd_path);
		temp++;
	}
	return (NULL);
}

char	*find_fullpath(char **envp, char *cmd)
{
	char	**path_arr;
	char	*full_cmd_path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	path_arr = ft_split(find_path(envp), ':');
	if (!path_arr)
		return (NULL);
	full_cmd_path = check_command_in_path(path_arr, cmd);
	free(path_arr);
	return (full_cmd_path);
}

/*
etrieve the value of the PATH environment variable from an array of
environment variables. The PATH variable contains a list of directories that
the system searches for executable files.
*/

	/*
Let's say the PATH environment variable is set as follows:
PATH=/usr/local/bin:/usr/bin:/bin
This means that the system will look for executables in the directories
/usr/local/bin, /usr/bin, and /bin, in that order.

char		*envp[] = {
	"PATH=/usr/local/bin:/usr/bin:/bin",
	NULL // End of environment variables
};
char		*cmd = "ls";
char		*full_path = cmd_path(envp, cmd);
Check Current Directory:
The function first checks if the command ls exists in the current directory
using	access(cmd, F_OK).
If ls is not found in the current directory, it proceeds to the next step.
Split the PATH Variable:

The function retrieves the PATH variable using var_path(envp),
which returns the string /usr/local/bin:/usr/bin:/bin.
It then splits this string into an array of directories using ft_split,
	resulting in:
path_arr = {"/usr/local/bin", "/usr/bin", "/bin", NULL};
The function enters a loop to iterate through each directory in path_arr.
heck Existence: The function checks if
	/usr/local/bin/ls exists using access(command, F_OK).
If it does not exist, it frees the allocated memory for command and continues to
the next iteration.
In this example, it checks for the existence of /usr/bin/ls.
If the command exists at that path, it can be executed directly
This function effectively locates executable commands b
based on the system's environment configuration.
dont need path if find cmd in local dir can run directly
It avoids assumptions about the environment, ensuring robustness across systems.
It adheres to the principle of fail-fast: detecting issues early and
preventing unpredictable runtime behavior.
 command will only execute once, in the first directory where it is found.

 you free path arr at the end in case no valid command is found for full path
 // Free the original memory after usage free(path_arr);
*/
