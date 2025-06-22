static int	run_builtin_command(const char *cmd, t_command *command, t_env_vars **env_vars)
{
	int	i;

	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(command->args, env_vars));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(command->args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(env_vars, command->args));
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		i = 1;
		while (command->args[i])
		{
			if (ft_unset(env_vars, command->args[i]) != 0)
				return (1);
			i++;
		}
		return (0);
	}
	else if (ft_strcmp(cmd, "env") == 0)
		return (env(*env_vars));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (exit_shell(env_vars));
	return (2); // Not a builtin
}