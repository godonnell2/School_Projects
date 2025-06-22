#include "minishell.h"

char	*get_current_directory(char *buf, size_t size)
{
	if (!getcwd(buf, size))
	{
		perror("cd: getcwd");
		return (NULL);
	}
	return (buf);
}

static int	cd_error(const char *msg)
{
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

static char	*get_cd_target(char **input, t_env_vars *env_list)
{
	if (!input[1])
		return (get_env_value(env_list, "HOME"));
	if (input[1][0] == '\0')
		return (strdup("")); // explicitly empty
	if (strcmp(input[1], "-") == 0)
		return (get_env_value(env_list, "OLDPWD"));
	return (input[1]);
}

int	ft_cd(char **input, t_env_vars **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*target;

	if (!get_current_directory(old_pwd, sizeof(old_pwd)))
		return (1);

	target = get_cd_target(input, *env_list);
	if (!target)
		return (cd_error("cd: too many arguments"));
	if (target[0] == '\0')
	{
		free(target);
		return (cd_error("cd: : No such file or directory"));
	}

	if (chdir(target) != 0)
	{
		perror("cd");
		if (target != input[1])
			free(target);
		return (1);
	}
	if (!get_current_directory(new_pwd, sizeof(new_pwd)))
	{
		if (target != input[1])
			free(target);
		return (1);
	}

	update_env_var(env_list, "OLDPWD", old_pwd);
	update_env_var(env_list, "PWD", new_pwd);

	if (input[1] && strcmp(input[1], "-") == 0)
	{
		write(STDOUT_FILENO, new_pwd, strlen(new_pwd));
		write(STDOUT_FILENO, "\n", 1);
	}

	if (target != input[1])
		free(target);
	return (0);
}
/*
static char	*change_no_argument(t_env_vars *env_list)
{
	char	*target;

	target = get_env_value(env_list, "HOME");
	if (!target)
	{
		perror("cd: HOME not set");
		return (NULL);
	}
	return (target);
}

static char	*get_cd_target(char **input, t_env_vars *env_list)
{
	char	*target;

	if (!input[1])
	{
		target = change_no_argument(env_list);
	}
	else
	{
		target = input[1];
	}
	return (target);
}

int	ft_cd(char **input, t_env_vars **env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*target;
	
	int arg_count = 0;
	while (input[arg_count])
		arg_count++;

	if (arg_count > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}

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

*/