#include "minishell.h"

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
	//need to make sure the next value is attached.
	return (0);
}

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
		write(2, "exit: numeric argument required\n", 31);
		clean_env_lst(env_list);
		exit(255);
	}
		if (args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		exit(1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	clean_env_lst(env_list);
	exit(exit_code);
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

// static int	get_curr_directory(char *buf, size_t size)
// {
// 	if (!getcwd(buf, size))
// 	{
// 		perror("cd: get cwd");
// 		return (0);
// 	}
// 	return (1);
// }

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
