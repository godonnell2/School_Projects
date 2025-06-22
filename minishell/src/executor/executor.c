#include "minishell.h"
#include <sys/stat.h>
//  onlu use heredoc if it's first cmd cos otherwise it's already written to pipe
// If there’s a heredoc, it should feed into STDIN.

// Every forked child inherits all pipe FDs.

// Child must close all other FDs it doesn't need.

void close_if_not_std(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
	{
		close(fd);
		DEBUG_LOG("Closed fd %d\n", fd);
	}
}

static void close_all_inherited_fds(t_inherited_fds *inherited_fds)
{
	DEBUG_LOG("Closing inherited fds\n");
	for (int i = 0; i < inherited_fds->inherited_fds_count; ++i)
	{
		close_if_not_std(inherited_fds->inherited_fds[i]);
	}
}

// Fail safely if redirection failed

// Now, before execve, you should close the file_fd's you opened.
// The standard fds (0, 1, 2) are already redirected via dup2.
// This is important to prevent file descriptor leaks.

static void execute_child(t_process *proc, t_env_vars *env_vars, char **env_arr, t_shell *shell)
{
	t_command *cmd = proc->cmd;

	if (apply_redirections(proc, shell) == -1)
		exit(shell->last_exit_code);

	if (proc->in_fd == -1 || proc->out_fd == -1)
	{
		DEBUG_LOG(" XXX invalid fds in child, exiting\n");
		exit(1);
	}

	if (proc->in_fd != STDIN_FILENO)
	{
		DEBUG_LOG(" 🔧 redirecting stdin  FD=%d\n", proc->in_fd);
		dup2(proc->in_fd, STDIN_FILENO);
	}

	if (proc->out_fd != STDOUT_FILENO)
	{
		DEBUG_LOG(" 🔧 redirecting stdout to FD=%d\n", proc->out_fd);
		dup2(proc->out_fd, STDOUT_FILENO);
	}

	close_all_inherited_fds(proc->inherited_fds);

	if (is_built_in(cmd))
	{
		int exit_code = execute_builtin(cmd, &env_vars);
		exit(exit_code);
	}
	
	if (access(cmd->full_path, F_OK) == 0)
	{
		if (access(cmd->full_path, X_OK) == 0)
		{
			execve(cmd->full_path, cmd->args, env_arr);
			perror("execve");
			exit(EXIT_FAILURE); // e.g. if file isn't ELF or has bad format
		}
		else
		{
			perror(cmd->full_path); // e.g. Permission denied
			DEBUG_LOG("cmd->full_path: %s\n", cmd->full_path);
			exit(126); // Exists but not executable
		}
	}
	else
	{
		// File doesn't exist at all
		DEBUG_LOG("access F_OK: %d, X_OK: %d\n", access(cmd->full_path, F_OK), access(cmd->full_path, X_OK));
		ft_putstr_fd(" command not found\n", 2);
		exit(127);
	}
}
static void fork_process(t_process *proc, t_env_vars *env_vars, char **env_arr, t_shell *shell)
{
	DEBUG_LOG("🟢 fork_process: Forking for command '%s'\n", proc->cmd->args[0]);
	pid_t pid;

	ignore_signals_before_fork(); // ignore temporarily right before fork
	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		set_signals_to_default(); // set default signal behaviour in child process
		execute_child(proc, env_vars, env_arr, shell);
	}
	else
	{
		DEBUG_LOG("🔵 Forked child PID=%d\n", pid);
		proc->pid = pid;
	}
}

void set_exit_code(t_shell *shell, int code)
{
	DEBUG_LOG("Setting shell->last_exit_code to %d\n", code);
	shell->last_exit_code = code;
}

static void wait_for_children(t_executor *ex, t_process *procs, t_shell *shell)
{
	int status;
	int i;

	i = 0;
	while (i < ex->cmd_count)
	{
		waitpid(procs[i].pid, &status, 0);
		if (WIFEXITED(status))
			set_exit_code(shell, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			set_exit_code(shell, 128 + WTERMSIG(status));
		i++;
	}
	handle_signals_in_exec(WTERMSIG(status)); // detecting exit signal and printing NL/quit msg
}

void print_cmd_list(t_command *cmd)
{
	int i = 0;
	while (cmd)
	{
		DEBUG_LOG("[CMD %d] %s\n", i, cmd->args[0]);
		cmd = cmd->next;
		i++;
	}
}

int has_input_redir(t_redirect *redirs)
{
	while (redirs)
	{
		if (redirs->type == REDIR_IN || redirs->type == HEREDOC)
			return 1;
		redirs = redirs->next;
	}
	return 0;
}

// for $EMPTY

void execute_pipes(t_command *cmd_list, char **env_arr, t_env_vars *env_vars, t_shell *shell)
{
	t_executor ex;

	ex.cmd_list = cmd_list;

	
	ex.cmd_count = 0;
	t_command *tmp = cmd_list;
	while (tmp)
	{
		ex.cmd_count++;
		tmp = tmp->next;
	}

	t_command *curr_cmd = cmd_list;

	if (ex.cmd_count == 1)
	{
		t_process tmp_proc;
		t_process *proc = &tmp_proc;
		init_proc(proc, curr_cmd);

		if (apply_redirections(proc, shell) == -1)
		{

			return;
		}

		// Now, after handling redirections, check if there's an actual command
		if (!curr_cmd->args || !curr_cmd->args[0])
		{
			// If it was just a redirection (e.g., "< infile") and the file existed/was handled,
			// then there's nothing more to do for this "empty" command.
			// The shell successfully processed the redirection.
			set_exit_code(shell, 0); // Bash exits 0 if file exists for `< file`
			// You might want to close the fds opened by apply_redirections here
			// if they haven't been dup2'd or used.
			close_if_not_std(proc->in_fd);
			close_if_not_std(proc->out_fd);
			return;
		}

		if (curr_cmd->args[0][0] == '\0')
		{
		
			ft_putstr_fd(": command not found\n", 2);
			set_exit_code(shell, 127);
			close_if_not_std(proc->in_fd); // Close fds opened by apply_redirections
			close_if_not_std(proc->out_fd);
			return;
		}
		if(ft_strchr(curr_cmd->args[0], '/'))
		{
			if (is_directory(curr_cmd->args[0]))
			{
			DEBUG_LOG("minishell: %s: Is a directory\n", curr_cmd->args[0]);
			set_exit_code(shell, 126);
			close_if_not_std(proc->in_fd);
			close_if_not_std(proc->out_fd);
			return;
			}
		}

		if (is_built_in(curr_cmd))
		{
			DEBUG_LOG("Executing builtin command '%s' directly in parent process...\n", curr_cmd->args[0]);

			int original_stdin = dup(STDIN_FILENO);
			int original_stdout = dup(STDOUT_FILENO);
			if (proc->in_fd != STDIN_FILENO)
				dup2(proc->in_fd, STDIN_FILENO);
			if (proc->out_fd != STDOUT_FILENO)
				dup2(proc->out_fd, STDOUT_FILENO);

			int exit_code = execute_builtin(curr_cmd, &env_vars);
			DEBUG_PRINTF("exit_code=%d | shell->last_exit_code=%d\n", exit_code, shell->last_exit_code);
			set_exit_code(shell, exit_code);
		
			dup2(original_stdin, STDIN_FILENO);
			dup2(original_stdout, STDOUT_FILENO);
			close_if_not_std(original_stdin);
			close_if_not_std(original_stdout);
			close_if_not_std(proc->in_fd);
			close_if_not_std(proc->out_fd);
			return; 
		}
	}
		DEBUG_LOG("Creating %d child processes...\n", ex.cmd_count); // Debugging
		t_process *procs = malloc(sizeof(t_process) * ex.cmd_count);
		init_proc(procs, curr_cmd);
		curr_cmd = curr_cmd->next;

		for (int i = 1; i < ex.cmd_count; i++)
		{
			init_proc(procs + i, curr_cmd);

			int pipe_fd[2];
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			DEBUG_LOG("Creating pipe proc[%d]->proc[%d] fd[%d]->fd[%d]\n", i - 1, i, pipe_fd[WRITE], pipe_fd[READ]);
			if (procs[i - 1].out_fd == STDOUT_FILENO)
			{
				// pipes have lower precedence than other output fds
				procs[i - 1].out_fd = pipe_fd[WRITE];
			}
			else
			{
				close(pipe_fd[WRITE]);
			}
			if (has_input_redir(curr_cmd->redirs) == 0)
				procs[i].in_fd = pipe_fd[READ];
			else
				close(pipe_fd[READ]);

			curr_cmd = curr_cmd->next;
		}

		t_inherited_fds inherited_fds;
		inherited_fds.inherited_fds_count = ex.cmd_count * 2;
		inherited_fds.inherited_fds = malloc(inherited_fds.inherited_fds_count * sizeof(int));
		for (int i = 0; i < ex.cmd_count; ++i)
		{
			int start_pos = i * 2;
			inherited_fds.inherited_fds[start_pos] = procs[i].in_fd;
			inherited_fds.inherited_fds[start_pos + 1] = procs[i].out_fd;
			procs[i].inherited_fds = &inherited_fds;
		}
		// shell->state = EXEC; //to ensure readline is not repeated in case of sigint during child process
		int child_index = 0;
		while (child_index < ex.cmd_count)
		{
			// Fork and execute the current command
			fork_process(procs + child_index, env_vars, env_arr, shell);
			child_index++;
		}
		close_all_inherited_fds(&inherited_fds);
		DEBUG_LOG("Waiting for child processes to finish...\n");
		wait_for_children(&ex, procs, shell);
		DEBUG_LOG("Waited!\n");
		free(inherited_fds.inherited_fds);
		// shell->state = IDLE; //reset to IDLE after execution
		free(procs);
	}
	// a fn that take a cmd and returns the child process

	/*

	void execute_pipes(t_command *cmd_list, char **env_arr, t_env_vars *env_vars, t_shell *shell)
	{
		t_executor ex;

		ex.cmd_list = cmd_list;

		// Count number of commands
		ex.cmd_count = 0;
		t_command *tmp = cmd_list;
		while (tmp)
		{
			ex.cmd_count++;
			tmp = tmp->next;
		}

		// print_cmd_list(cmd_list);
		//  init procs
		t_command *curr_cmd = cmd_list;


		if (!curr_cmd || !curr_cmd->args || !curr_cmd->args[0])
		{
			set_exit_code(shell, 0);
			return;
		}

		if (curr_cmd->args[0][0] == '\0')
		{
			ft_putstr_fd(": command not found\n", 2);
			set_exit_code(shell, 127);
			return;
		}
		if (  is_directory(cmd_list->args[0]))
		{
			DEBUG_LOG("is dir in exec pipes\n");
			return;
		}

		if (is_built_in(curr_cmd) && ex.cmd_count == 1)
		{
			// If only one command and it's a builtin, execute it directly
			DEBUG_LOG("Executing builtin command '%s' directly in parent process...\n", curr_cmd->args[0]); // Debugging
			t_process tmp;
			t_process *proc = &tmp;
			DEBUG_LOG("Executing builtin command '%s' directly in parent process...\n", curr_cmd->args[0]);

			init_proc(proc, curr_cmd);


			if (apply_redirections(proc, shell) == -1)
			{
				set_exit_code(shell, 1);
				return;
			}

			int prev_in = -1, prev_out = -1;
			// step1: set up file descriptors in the current process
			// Pipe redirections — if any pipe fds are set, redirect them
			// as per proc.
			if (proc->in_fd == -1 || proc->out_fd == -1)
			{
				set_exit_code(shell, 1);
				return;
			}

			if (proc->in_fd != STDIN_FILENO)
			{
				prev_in = dup(STDIN_FILENO);
				DEBUG_LOG("redirecting stdin  FD=%d\n", proc->in_fd);
				dup2(proc->in_fd, STDIN_FILENO);
				close(proc->in_fd);
			}

			// --- 2. Handle stdout: pipe --- // Save & redirect stdout
			if (proc->out_fd != STDOUT_FILENO)
			{
				prev_out = dup(STDOUT_FILENO);

				DEBUG_LOG("Redirecting stdout to current pipe FD=%d\n", proc->out_fd);
				dup2(proc->out_fd, STDOUT_FILENO);
				close(proc->out_fd);
			}

			int exit_code = execute_builtin(curr_cmd, &env_vars);
			DEBUG_PRINTF("exit_code=%d | shell->last_exit_code=%d\n", exit_code, shell->last_exit_code);
			set_exit_code(shell, exit_code);
			DEBUG_PRINTF("after store in struct exit_code=%d\n", shell->last_exit_code);
			// step2: undo step1 and close
			if (prev_in != -1)
			{
				dup2(prev_in, STDIN_FILENO);
				close(prev_in);
			}
			if (prev_out != -1)
			{
				dup2(prev_out, STDOUT_FILENO);
				close(prev_out);
			}
			return;
		}

		DEBUG_LOG("Creating %d child processes...\n", ex.cmd_count); // Debugging
		t_process *procs = malloc(sizeof(t_process) * ex.cmd_count);
		init_proc(procs, curr_cmd);
		curr_cmd = curr_cmd->next;

		for (int i = 1; i < ex.cmd_count; i++)
		{
			init_proc(procs + i, curr_cmd);

			int pipe_fd[2];
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			DEBUG_LOG("Creating pipe proc[%d]->proc[%d] fd[%d]->fd[%d]\n", i - 1, i, pipe_fd[WRITE], pipe_fd[READ]);
			if (procs[i - 1].out_fd == STDOUT_FILENO)
			{
				// pipes have lower precedence than other output fds
				procs[i - 1].out_fd = pipe_fd[WRITE];
			}
			else
			{
				close(pipe_fd[WRITE]);
			}
			if (has_input_redir(curr_cmd->redirs) == 0)
				procs[i].in_fd = pipe_fd[READ];
			else
				close(pipe_fd[READ]);

			curr_cmd = curr_cmd->next;
		}

		t_inherited_fds inherited_fds;
		inherited_fds.inherited_fds_count = ex.cmd_count * 2;
		inherited_fds.inherited_fds = malloc(inherited_fds.inherited_fds_count * sizeof(int));
		for (int i = 0; i < ex.cmd_count; ++i)
		{
			int start_pos = i * 2;
			inherited_fds.inherited_fds[start_pos] = procs[i].in_fd;
			inherited_fds.inherited_fds[start_pos + 1] = procs[i].out_fd;
			procs[i].inherited_fds = &inherited_fds;
		}
		//shell->state = EXEC; //to ensure readline is not repeated in case of sigint during child process
		int child_index = 0;
		while (child_index < ex.cmd_count)
		{
			// Fork and execute the current command
			fork_process(procs + child_index, env_vars, env_arr, shell);
			child_index++;
		}
		close_all_inherited_fds(&inherited_fds);
		DEBUG_LOG("Waiting for child processes to finish...\n");
		wait_for_children(&ex, procs, shell);
		DEBUG_LOG("Waited!\n");
		free(inherited_fds.inherited_fds);
		//shell->state = IDLE; //reset to IDLE after execution
		free(procs);
	}
	*/