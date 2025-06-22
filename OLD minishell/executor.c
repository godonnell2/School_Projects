#include "minishell.h"

#define DUMP_FDS()

// #define DUMP_FDS()                                        \
	// do                                                    \
	// {                                                     \
		// printf("🔍 Dumping FDs for PID=%d:\n", getpid()); \
		// system("ls -l /proc/self/fd || ls -l /dev/fd");   \
	// } while (0)

int ft_wordlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

void ft_putstring_fd(char *s, int fd)
{
	write(fd, s, ft_wordlen(s));
}

char *strndup(const char *s, size_t n)
{
	char *d;

	d = malloc(n + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, n);
	d[n] = '\0';
	return (d);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	unsigned char *cs1;
	unsigned char *cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (i < n && (cs1[i] || cs2[i]))
	{
		if (cs1[i] != cs2[i])
		{
			return (cs1[i] - cs2[i]);
		}
		i++;
	}
	return (0);
}

void ft_strcpy(char *src, char *dst)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char *cat_strs_char(char *dest, const char *src1, char c, const char *src2)
{
	size_t i;

	i = 0;
	if (!src1 || !src2)
	{
		return (NULL);
	}
	while (*src1)
	{
		dest[i++] = *src1++;
	}
	dest[i++] = c;
	while (*src2)
	{
		dest[i++] = *src2++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t count_words(char const *s, char c)
{
	size_t i;
	size_t word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word_count);
}

static void skip_separators(const char **s, char sep)
{
	while (**s == sep)
	{
		(*s)++;
	}
}

char **ft_split_buff(char const *s, char sep, void *buff)
{
	const char *start;
	t_split_state curr;

	curr.buff_offset = 0;
	curr.word_count = count_words(s, sep);
	curr.arr = (char **)(buff + curr.buff_offset);
	curr.buff_offset += sizeof(char *) * (curr.word_count + 1);
	curr.word = 0;
	while (*s)
	{
		skip_separators(&s, sep);
		start = s;
		while (*s && *s != sep)
			s++;
		curr.word_len = s - start;
		if (curr.buff_offset + curr.word_len + 1 > SPLIT_BUFF_SIZE)
			return (NULL);
		curr.arr[curr.word] = (char *)buff + curr.buff_offset;
		ft_memcpy(curr.arr[curr.word], start, curr.word_len);
		curr.arr[curr.word++][curr.word_len] = '\0';
		curr.buff_offset += curr.word_len + 1;
		skip_separators(&s, sep);
	}
	curr.arr[curr.word] = NULL;
	return (curr.arr);
}

static char *create_env_string(char *key, char *value)
{
	int len_key;
	char *env_str;
	int len_total;

	len_key = ft_wordlen(key);
	len_total = len_key + ft_strlen(value) + 2;
	env_str = malloc(len_total);
	if (!env_str)
		return (NULL);
	ft_strcpy(key, env_str);
	env_str[len_key] = '=';
	ft_strcpy(value, env_str + len_key + 1);
	return (env_str);
}

static int count_env_nodes(t_env_vars *env_vars)
{
	int count;

	count = 0;
	while (env_vars)
	{
		count++;
		env_vars = env_vars->next;
	}
	return (count);
}

// IS FREEING CORECT ???
// printf("ENV: %s=%s\n", curr->key, curr->value);
char **convert_env_to_array(t_env_vars *env_vars)
{
	int count;
	const t_env_vars *curr;
	char **env_arr;
	int i;

	count = count_env_nodes(env_vars);
	env_arr = malloc(sizeof(char *) * (count + 1));
	if (!env_arr)
		return (NULL);
	curr = env_vars;
	i = 0;
	while (curr)
	{
		env_arr[i] = create_env_string(curr->key, curr->value);
		if (!env_arr[i])
		{
			while (--i >= 0)
				free(env_arr[i]);
			free(env_arr);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void free_env_array(char **env_array)
{
	char **tmp;

	if (!env_array)
		return;
	tmp = env_array;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(env_array);
}

static int execute_builtin(t_command *command, t_env_vars **env_vars)
{
	const char *cmd = command->args[0];
	int i;

	if (!command || !command->args || !command->args[0])
	{
		printf("Error: Invalid command structure\n");
		return 1;
	}
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
		return (exit_shell(command->args, env_vars));
	return 0;
}

char *get_path_variable(t_env_vars *env_vars)
{
	t_env_vars *current;

	current = env_vars;
	printf("IN GET_PATH_VAR Checking env var: %s=%s\n", env_vars->key, env_vars->value); // DEBUG
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", 5) == 0)
		{
			printf("IN_GET_PATH _VARFound PATH: %s\n", env_vars->value); // Debugging
			return (current->value);
		}
		current = current->next;
	}
	printf("INGETPATHVAR: PATH variable not found.\n"); // Debugging
	return (NULL);
}

void check_command_in_path(char **path_arr, char *cmd, char *full_path)
{
	size_t p_len;
	size_t c_len;
	char **temp_patharr;

	temp_patharr = path_arr;
	while (*temp_patharr != NULL)
	{
		p_len = ft_wordlen(*temp_patharr);
		c_len = ft_wordlen(cmd);
		if ((p_len + c_len + 2) > PATH_MAX)
			return;
		cat_strs_char(full_path, *temp_patharr, '/', cmd);
		printf("Resolved path: %s\n", full_path); // Debugging
		if (access(full_path, X_OK) == 0)
			return;
		temp_patharr++;
	}
	full_path[0] = '\0';
}
/// usr/bin:/bin
void resolve_command_full_path(t_env_vars *env_vars, char *cmd,
							   char *full_path)
{
	char buff[SPLIT_BUFF_SIZE];
	char **path_arr;
	char *path_env;
	printf("calling resolve command full path\n"); // DEBUG

	full_path[0] = '\0';
	if (access(cmd, X_OK) == 0)
	{
		ft_strcpy(cmd, full_path);
		printf("cmd;%s full_path:%s", cmd, full_path); // DEBUG
		return;
	}
	printf("in resolve command path function print env/\n"); ////DEBUG
	// print_env_vars(env_vars);								 // DEBUGGING
	path_env = get_path_variable(env_vars);
	if (!path_env)
	{
		printf("No PATH variable found.\n"); // Debugging
		return;
	}
	printf("PATH variable: %s\n", path_env); // Debugging
	path_arr = ft_split_buff(path_env, ':', buff);
	check_command_in_path(path_arr, cmd, full_path);
}

// If heredoc_fd is set, we need to USE that and IGNORE infile.
// otherwise we can fallback to infile
static void setup_input_redirection(t_command *cmd)
{
	int fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->heredoc_fd != -1)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
}

// bitwise ops
//  write only for curr process
//  TRUNC does not append it overwrites,
//  needs to clear it otherwise when writing could have left over bits
//  0 means its in octal form (base 8)
//  6 owner Read (4) + Write (2) = 6
// 4 group Read (4) = 4
//  4 others Read (4) = 4
static void setup_output_redirection(t_command *cmd)
{
	int fd;
	int flags;

	if (!cmd->outfile)
		return;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append_out)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void setup_redirections(t_command *cmd)
{
	setup_input_redirection(cmd);
	setup_output_redirection(cmd);
}

void prep_heredocs(t_command *cmds)
{
	t_command *curr = cmds;

	while (curr != NULL)
	{
		if (curr->heredoc_eof != NULL)
		{
			curr->heredoc_fd = ft_heredoc(curr->heredoc_eof);
		}
		curr = curr->next;
	}
}
// we close read end of child cos its not used by curr process, instead we use write end of curr
//  and read from prev pipe fd
//  exit 127 = command not found
//  onlu use heredoc if it's first cmd cos otherwise it's already written to pipe
// If there’s a heredoc, it should feed into STDIN.
// Else if ex->prev_pipe_fd != -1, pipe input should be fed into STDIN.
// redirect stdout to pipe
//  Redirect stdin from the previous pipe
static void execute_child(t_child_process *proc, t_env_vars *env_vars, char **env_arr)
{
	t_command *cmd = proc->cmd;

	fprintf(stderr, "🔧 Child PID=%d preparing redirections for command '%s'...\n", getpid(), cmd->args[0]);

	if (proc->pipe_fd[READ] != STDIN_FILENO)
	{
		fprintf(stderr, "    [DEBUG][%d] redirecting stdin  FD=%d\n", getpid(), proc->pipe_fd[READ]);
		dup2(proc->pipe_fd[READ], STDIN_FILENO);
		close(proc->pipe_fd[READ]);
	}
	else
	{
		fprintf(stderr, "    [DEBUG][%d] stdin not redirected.\n", getpid());
	}

	// --- 2. Handle stdout: pipe ---
	if (proc->pipe_fd[WRITE] != STDOUT_FILENO)
	{
		fprintf(stderr, "    [DEBUG][%d] redirecting stdout to current pipe FD=%d\n", getpid(), proc->pipe_fd[WRITE]);
		dup2(proc->pipe_fd[WRITE], STDOUT_FILENO);
		close(proc->pipe_fd[WRITE]);
	}
	else
	{
		fprintf(stderr, "    [DEBUG][%d] stdout not redirected.\n", getpid());
	}

	fprintf(stderr, "    [DEBUG][%d] ✅ FDs now: stdin=%d, stdout=%d\n", getpid(), proc->pipe_fd[READ], proc->pipe_fd[WRITE]);

	if (is_built_in(cmd))
	{
		int exit_code = execute_builtin(cmd, &env_vars);
		exit(exit_code);
	}

	if (cmd->full_path && access(cmd->full_path, X_OK) == 0)
	{
		fprintf(stderr, "    [DEBUG][%d] 🟠 Executing external: %s\n", getpid(), cmd->full_path);
		DUMP_FDS();
		execve(cmd->full_path, cmd->args, env_arr);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "   [DEBUG][%d] ❌ Command not found: %s\n", getpid(), cmd->args[0]);
	free_env_vars(env_vars);
	exit(127);
}
// close prev pipe if necss , prep for next cmds input and close heredoc if used
// ** PARENT PIPE HANDLING - Corrected **
static void handle_parent(t_child_process *proc)
{
	// Close the write end of the pipe in the parent process

	// todo close pipes in parent
	if (proc->pipe_fd[WRITE] != STDOUT_FILENO)
	{
		fprintf(stderr, "    [DEBUG] Parent closing write end of pipe FD=%d of PID=%d\n",
				proc->pipe_fd[WRITE],
				proc->pid);
		close(proc->pipe_fd[WRITE]);
	}
	else
	{
		fprintf(stderr, "    [DEBUG] Parent write end of pipe not closed of PID=%d.\n", proc->pid);
	}
	// if (ex->curr_cmd->next != NULL)
	// {
	// 	close(ex->pipe_fd[WRITE]);
	// 	ex->prev_pipe_fd = ex->pipe_fd[READ]; // Next command uses this
	// }
	// else
	// {
	// 	close(ex->pipe_fd[READ]);
	// 	close(ex->pipe_fd[WRITE]);
	// }

	// ex->pipe_fd[READ] = -1;
	// ex->pipe_fd[WRITE] = -1;
}
// oly create pipe IF there's a next cmd
// static void create_pipe_if_needed(t_executor *ex)
// {
// 	if (ex->curr_cmd->next != NULL)
// 	{
// 		if (pipe(ex->pipe_fd) < 0)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 	}

// 	else
// 	{
// 		ex->pipe_fd[READ] = -1;
// 		ex->pipe_fd[WRITE] = -1;
// 	}
// 	printf("Pipe created: read_fd=%d, write_fd=%d\n", ex->pipe_fd[0], ex->pipe_fd[1]);
// }

static void fork_process(t_child_process *proc, t_env_vars *env_vars, char **env_arr)
{
	printf("🟢 fork_process: Forking for command '%s'\n", proc->cmd->args[0]); // 🟢 Debug
	pid_t pid;

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
		execute_child(proc, env_vars, env_arr);
	else
	{
		// printf("🚨 DEBUG: FDs in child after dup2s:\n");
		// for (int fd = 0; fd < 10; fd++)
		// {
		// 	if (fcntl(fd, F_GETFD) != -1)
		// 		printf("    FD %d is open\n", fd);
		// }
		printf("🔵 Parent PID=%d forked child PID=%d\n", getpid(), pid); // 🔵 Debug
		proc->pid = pid;
		handle_parent(proc);
	}
}

static void wait_for_children(t_executor *ex, t_child_process *procs)
{
	int status;
	int i;

	i = 0;
	while (i < ex->cmd_count)
	{
		waitpid(procs[i].pid, &status, 0);
		if (WIFEXITED(status))
			ex->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ex->last_exit_code = 128 + WTERMSIG(status);
		i++;
	}
}
// THIS LOOP SHOULD GET EVERYTHIHNG TO START AT SAME TIME and we are passing SLEEP YAYAY
//  ONE SPECIAL CASE WHERE YOU DONT WANT TO FORK! ONLY ONE BUILTIN IN WHOLE PIPELINE and
//  then you run builtin directly in parent shell, affects env/cwd as expected
void execute_pipes(t_command *cmd_list, char **env_arr, t_env_vars *env_vars)
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

	if (ex.cmd_count == 0)
	{
		fprintf(stderr, "No commands to execute.\n");
		return;
	}

	// Prepare heredocs first (before forking)
	prep_heredocs(cmd_list);

	printf("Creating %d child processes...\n", ex.cmd_count); // Debugging
	t_child_process *procs = malloc(sizeof(t_child_process) * ex.cmd_count);

	// init procs
	t_command *curr_cmd = cmd_list;
	procs[0].cmd = curr_cmd;
	// READ: todo handle heredoc/file
	procs[0].pipe_fd[READ] = curr_cmd->heredoc_fd != 0 ? curr_cmd->heredoc_fd : STDIN_FILENO;
	// WRITE: may be overwritten by next cmd
	procs[0].pipe_fd[WRITE] = STDOUT_FILENO;
	curr_cmd = curr_cmd->next;

	for (int i = 1; i < ex.cmd_count; i++)
	{
		procs[i].cmd = curr_cmd;
		// WRITE may be overwritten by next cmd
		procs[i].pipe_fd[WRITE] = STDOUT_FILENO;

		curr_cmd = curr_cmd->next;
		int pipe_fd[2];
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		printf("Creating pipe proc[%d]->proc[%d] fd[%d]->fd[%d]\n", i - 1, i, pipe_fd[WRITE], pipe_fd[READ]);
		procs[i - 1].pipe_fd[WRITE] = pipe_fd[WRITE];
		procs[i].pipe_fd[READ] = pipe_fd[READ];
	}

	int child_index = 0;
	while (child_index < ex.cmd_count)
	{
		// Fork and execute the current command
		fork_process(procs + child_index, env_vars, env_arr);

		// Safe to close the last read end *after* the next command has forked
		// if (last_prev_pipe_fd != -1)
		// {
		// 	close(last_prev_pipe_fd);
		// 	last_prev_pipe_fd = -1;
		// }

		// Save the read end for next iteration (to be closed later)
		// last_prev_pipe_fd = ex.prev_pipe_fd;

		// Move to the next command in the pipeline
		// ex.curr_cmd = ex.curr_cmd->next;
		child_index++;
	}

	printf("Waiting for child processes to finish...\n");
	wait_for_children(&ex, procs);
	printf("Waited!\n");

	free(procs);
}

int is_built_in(t_command *cmd)
{
	const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
							  "exit", NULL};

	const char **builtin_ptr = builtins;
	if (!cmd || !cmd->args[0])
		return 0;

	while (*builtin_ptr)
	{
		if (ft_strcmp(cmd->args[0], *builtin_ptr) == 0)
		{
			return 1;
			break;
		}
		builtin_ptr++;
	}

	return 0;
}

void resolve_all_command_paths(t_env_vars *env_vars, t_command *cmds)
{
	char full_path[PATH_MAX];
	int builtin;
	t_command *curr = cmds;

	printf("resolve_command_full_path: env_vars pointer = %p\n", (void *)env_vars); // DEBUG
	while (curr != NULL)															// cmds != NULL
	{
		builtin = is_built_in(curr);
		if (!builtin)
		{
			resolve_command_full_path(env_vars, curr->args[0], full_path);
			printf("  Resolved path: '%s'\n", full_path); // DEBUG
			if (full_path[0] != '\0')
			{
				curr->full_path = ft_strdup(full_path);
				if (!curr->full_path)
				{
					perror("ft_strdup");
					curr->full_path = NULL;
				}
			}
			else
			{
				printf("  [WARNING] Empty path for command '%s'\n", curr->args[0]); // DEBUG
			}
		}
		else
		{
			curr->full_path = NULL; // nopath for builtings
		}
		curr = curr->next;
		// cmds = cmds->next;
	}
}