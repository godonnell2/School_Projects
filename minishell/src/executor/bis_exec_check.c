#include "minishell.h"

int	is_built_in(t_command *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};
	const char	**builtin_ptr = builtins;

	if (!cmd || !cmd->args ||  !cmd->args[0])
		return (0);
	while (*builtin_ptr)
	{
		if (ft_strcmp(cmd->args[0], *builtin_ptr) == 0)
		{
			return (1);
			break ;
		}
		builtin_ptr++;
	}
	return (0);
}

static int	handle_unset(t_command *command, t_env_vars **env_vars)
{
	int	i;

	i = 1;
	while (command->args[i])
	{
		if (ft_unset(env_vars, command->args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(t_command *command, t_env_vars **env_vars)
{
	const char	*cmd = command->args[0];

	if (!command || !command->args || !command->args[0])
	{
		printf("Error: Invalid command structure\n");
		return (1);
	}
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(command->args, env_vars));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(env_vars, command->args));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(command->args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "unset") == 0)
		return (handle_unset(command, env_vars));
	else if (ft_strcmp(cmd, "env") == 0)
		return (env(*env_vars));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (exit_shell(command->args, env_vars));
	return (0);
}
