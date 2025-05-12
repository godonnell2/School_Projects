static void	execute_child(t_executor *ex)
{
	t_command	*cmd;

	cmd = &ex->commands[ex->cmd_idx];
	// Set up pipe redirections
	if (ex->cmd_idx > 0)
	{
		dup2(ex->prev_pipe_fd, STDIN_FILENO);
		close(ex->prev_pipe_fd);
	}
	if (ex->cmd_idx < ex->cmd_count - 1)
	{
		dup2(ex->pipe_fd[WRITE], STDOUT_FILENO);
		close(ex->pipe_fd[WRITE]);
	}
	// Handle file redirections
	setup_redirections(cmd);
	// Execute command
	if (cmd->full_path && access(cmd->full_path, X_OK) == 0)
	{
		execve(cmd->full_path, cmd->args, ex->env_array);
	}
	perror("execve");
	exit(EXIT_FAILURE);
}

/* ================== */
/*  Parent Bookkeeping */
/* ================== */
static void	handle_parent(t_executor *ex)
{
	// Close previous pipe read end
	if (ex->cmd_idx > 0)
	{
		close(ex->prev_pipe_fd);
	}
	// Prepare for next command
	if (ex->cmd_idx < ex->cmd_count - 1)
	{
		close(ex->pipe_fd[WRITE]);
		ex->prev_pipe_fd = ex->pipe_fd[READ];
	}
}

/* ================== */
/*  Main Pipe Logic   */
/* ================== */
void	execute_pipes(t_command *commands, int num_commands, char **env_array)
{
	t_executor	ex = {.prev_pipe_fd = -1, .pids = malloc(sizeof(pid_t)
				* num_commands), .cmd_count = num_commands,
			.env_array = env_array, .commands;

	ex = {.prev_pipe_fd = -1, .pids = malloc(sizeof(pid_t)  num_commands),
		.cmd_count = num_commands, .env_array = env_array,
		.commands = commands};
	for (ex.cmd_idx = 0; ex.cmd_idx < num_commands; ex.cmd_idx++)
	{
		// Create pipe for all commands except last
		if (ex.cmd_idx < num_commands - 1 && pipe(ex.pipe_fd) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// Fork process
		if ((ex.pids[ex.cmd_idx] = fork()) < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (ex.pids[ex.cmd_idx] == 0)
		{
			execute_child(&ex);
		}
		else
		{
			handle_parent(&ex);
		}
	}
	// Wait for all children
	wait_for_children(&ex);
	free(ex.pids);
}
