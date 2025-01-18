/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:11:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/17 15:56:06 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path_variable(char **envp)
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
			return (path);
		}
		i++;
	}
	return (NULL);
}

// F_OK check if file(cmd) exists regardless of permissions

static void	check_command_in_path(char **path_arr, char *cmd, char *full_path)
{
	size_t	p_len;
	size_t	c_len;
	char	**temp_patharr;

	temp_patharr = path_arr;
	while (*temp_patharr != NULL)
	{
		p_len = ft_wordlen(*temp_patharr);
		c_len = ft_wordlen(cmd);
		if ((p_len + c_len + 2) > PATH_MAX)
			return ;
		cat_strs_char(full_path, *temp_patharr, '/', cmd);
		if (access(full_path, F_OK) == 0)
			return ;
		temp_patharr++;
	}
	full_path[0] = '\0';
}

void	resolve_command_full_path(char **envp, char *cmd, char *full_path)
{
	char	buff[SPLIT_BUFF_SIZE];
	char	**path_arr;
	char	*path_env;

	full_path[0] = '\0';
	if (access(cmd, F_OK) == 0)
	{
		ft_strcpy(cmd, full_path);
		return ;
	}
	path_env = get_env_path_variable(envp);
	if (!path_env)
		return ;
	path_arr = ft_split_buff(path_env, ':', buff);
	check_command_in_path(path_arr, cmd, full_path);
}

// if ls exists in current folder you copy it to full path and return
//  otherwise PATH=/usr/local/bin:/usr/bin:/bin
//  path_arr[0] = "/usr/local/bin"
// path_arr[1] = "/usr/bin"
// path_arr[2] = "/bin"
// path_arr[3] = NULL // Null-terminated

/*
etrieve the value of the PATH environment variable from an array of
environment variables. The PATH variable contains a list of directories that
the system searches for executable files.
*/
/*
char		*envp[] = {
"PATH=/usr/local/bin:/usr/bin:/bin",
NULL // End of environment variables
};
char		*cmd = "ls";
char		*full_path = cmd_path(envp, cmd);

path_arr = {"/usr/local/bin", "/usr/bin", "/bin", NULL};

In this example, it checks for the existence of /usr/bin/ls.



*/
