#include "minishell.h"
#include <fcntl.h>
#include <stdio.h> //has to come before readline
#include <stdlib.h>
#include <unistd.h>
#define READ 0
#define WRITE 1
#define STDIN 0
#define SPLIT_BUFF_SIZE 102400

// AsK BETH IF WE CAN ADD TO HEAD THIS EXEC STRUCT
typedef struct s_executor
{
	int			pipe_fd[2];
	int			prev_pipe_fd;
	pid_t		*pids;
	int			last_exit_code;
	int cmd_count;       // Total commands in pipeline
	int cmd_i;           // Current command index (renamed)
	char **env_array;    // Environment variables
	t_command *commands; // Commands array
}				t_executor;

typedef struct s_split_state
{
	size_t		buff_offset;
	size_t		word_count;
	char		**arr;
	size_t		word;
	size_t		word_len;
}				t_split_state;

// Function prototypes
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			check_command_in_path(char **path_arr, char *cmd,
					char *full_path);
char			*get_env_path_variable(char **envp);
void			resolve_command_full_path(t_env_vars *env_vars, char *cmd,
					char *full_path);

int	ft_wordlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

void	ft_putstring_fd(char *s, int fd)
{
	write(fd, s, ft_wordlen(s));
}

char	*strndup(const char *s, size_t n)
{
	char	*d;

	d = malloc(n + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, n);
	d[n] = '\0';
	return (d);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

void	ft_strcpy(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*cat_strs_char(char *dest, const char *src1, char c, const char *src2)
{
	size_t	i;

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

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	word_count;

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

static void	skip_separators(const char **s, char sep)
{
	while (**s == sep)
	{
		(*s)++;
	}
}

char	**ft_split_buff(char const *s, char sep, void *buff)
{
	const char		*start;
	t_split_state	curr;

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

static char	*create_env_string(char *key, char *value)
{
	int		len_key;
	char	*env_str;
	int		len_total;

	len_key = ft_wordlen(key);
	len_total = len_key + ft_wordlen(value) + 2;
	env_str = malloc(len_total);
	if (!env_str)
		return (NULL);
	ft_strcpy(env_str, key);
	env_str[len_key] = '=';
	ft_strcpy(env_str + len_key + 1, value);
	return (env_str);
}

static int	count_env_nodes(t_env_vars *env_vars)
{
	int	count;

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
char	**convert_env_to_array(t_env_vars *env_vars)
{
	int			count;
	t_env_vars	*curr;
	char		**env_arr;
	int			i;

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
			free_env_vars(env_vars);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	free_env_array(char **env_array)
{
	char	**tmp;

	if (!env_array)
		return ;
	tmp = env_array;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(env_array);
}

// TOO LONG
static int	execute_builtin(t_command *command, t_env_vars **env_vars)
{
	const char	*cmd = command->args[0];
	int			i;

	if (!command || !command->args || !command->args[0])
	{
		printf("Error: Invalid command structure\n");
		return (1);
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
		return (exit_shell(env_vars));
	return (2);
}

char	*get_path_variable(t_env_vars *env_vars)
{
	t_env_vars	*current;

	current = env_vars;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", 5) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	check_command_in_path(char **path_arr, char *cmd, char *full_path)
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
		if (access(full_path, X_OK) == 0)
			return ;
		temp_patharr++;
	}
	full_path[0] = '\0';
}

void	resolve_command_full_path(t_env_vars *env_vars, char *cmd,
		char *full_path)
{
	char	buff[SPLIT_BUFF_SIZE];
	char	**path_arr;
	char	*path_env;

	full_path[0] = '\0';
	if (access(cmd, X_OK) == 0)
	{
		ft_strcpy(cmd, full_path);
		return ;
	}
	path_env = get_path_variable(env_vars);
	if (!path_env)
		return ;
	path_arr = ft_split_buff(path_env, ':', buff);
	check_command_in_path(path_arr, cmd, full_path);
}

static void	setup_input_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	setup_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return ;
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

static void	setup_redirections(t_command *cmd)
{
	setup_input_redirection(cmd);
	setup_output_redirection(cmd);
}

static void	execute_child(t_executor *ex)
{
	t_command	*cmd;

	cmd = &ex->commands[ex->cmd_i];
	if (ex->cmd_i > 0)
	{
		dup2(ex->prev_pipe_fd, STDIN_FILENO);
		close(ex->prev_pipe_fd);
	}
	if (ex->cmd_i < ex->cmd_count - 1)
	{
		dup2(ex->pipe_fd[WRITE], STDOUT_FILENO);
		close(ex->pipe_fd[WRITE]);
	}
	setup_redirections(cmd);
	if (cmd->full_path && access(cmd->full_path, X_OK) == 0)
	{
		execve(cmd->full_path, cmd->args, ex->env_array);
	}
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	handle_parent(t_executor *ex)
{
	if (ex->cmd_i > 0)
	{
		close(ex->prev_pipe_fd);
	}
	if (ex->cmd_i < ex->cmd_count - 1)
	{
		close(ex->pipe_fd[WRITE]);
		ex->prev_pipe_fd = ex->pipe_fd[READ];
	}
}

static void	create_pipe_if_needed(t_executor *ex)
{
	if (ex->cmd_i < ex->cmd_count - 1)
	{
		if (pipe(ex->pipe_fd) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

static void	fork_process(t_executor *ex)
{
	pid_t	pid;

	pid = fork();
	ex->pids[ex->cmd_i] = pid;
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

static void	wait_for_children(t_executor *ex)
{
	int	status;
	int	i;

	i = 0;
	while (i < ex->cmd_count)
	{
		waitpid(ex->pids[i], &status, 0);
		if (WIFEXITED(status))
			ex->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ex->last_exit_code = 128 + WTERMSIG(status);
		i++;
	}
}

void	execute_pipes(t_command *commands, int num_commands, char **env_array)
{
	t_executor	ex;

	ex = (t_executor){.prev_pipe_fd = -1, .pids = malloc(sizeof(pid_t)
			* num_commands), .cmd_count = num_commands, .env_array = env_array,
		.commands = commands, .cmd_i = 0};
	while (ex.cmd_i < num_commands)
	{
		create_pipe_if_needed(&ex);
		fork_process(&ex);
		if (ex.pids[ex.cmd_i] == 0)
			execute_child(&ex);
		else
			handle_parent(&ex);
		ex.cmd_i++;
	}
	wait_for_children(&ex);
	free(ex.pids);
}

// TOO LONG
void	resolve_all_command_paths(t_env_vars *env_vars, t_command *commands,
		int num_commands)
{
	char		full_path[PATH_MAX];
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};
	int			i;
	int			is_builtin;
	const char	**builtin_ptr = builtins;

	i = 0;
	while (i < num_commands)
	{
		is_builtin = 0;
		while (*builtin_ptr)
		{
			if (ft_strcmp(commands[i].args[0], *builtin_ptr) == 0)
			{
				is_builtin = 1;
				break ;
			}
			builtin_ptr++;
		}
		if (!is_builtin)
		{
			resolve_command_full_path(env_vars, commands[i].args[0], full_path);
			if (full_path[0] != '\0')
				commands[i].full_path = strdup(full_path);
		}
		else
			commands[i].full_path = NULL;
		i++;
	}
}
// void setup_commands(t_command *commands)
// {
//     commands[0].args = malloc(sizeof(char *) * 3);
//     commands[0].args[0] = strdup("ls");
//     commands[0].args[1] = strdup("-l");
//     commands[0].args[2] = NULL;
//     commands[0].infile = NULL;
//     commands[0].outfile = NULL;
//     commands[0].append_out = 0;
// }
// void setup_commands(t_command *commands)
// {
//     commands[0].args = malloc(sizeof(char *) * 4);
//     commands[0].args[0] = strdup("echo");
//     commands[0].args[1] = strdup("-n");
//     commands[0].args[2] = "this is a test";
//     commands[0].args[3] = NULL;
//     commands[0].infile = NULL;
//     commands[0].outfile = NULL;
//     commands[0].append_out = 0;
//     commands[0].full_path = NULL;
// }
// void	setup_commands(t_command *commands)
// {
// 	commands[0].args = malloc(sizeof(char *) * 3);
// 	commands[0].args[0] = strdup("cd");
// 	commands[0].args[1] = NULL;
// 	commands[0].args[2] = NULL;
// 	commands[0].infile = NULL;
// 	commands[0].outfile = NULL;
// 	commands[0].append_out = 0;
// 	commands[0].full_path = NULL;
// }

// void	setup_commands(t_command *commands)
// {
// 	commands[0].args = malloc(sizeof(char *) * 3);
// 	commands[0].args[0] = strdup("export");
// 	commands[0].args[1] =  strdup("MYVAR=test_value");
// 	commands[0].args[2] = NULL;
// 	commands[0].infile = NULL;
// 	commands[0].outfile = NULL;
// 	commands[0].append_out = 0;
// 	commands[0].full_path = NULL;
// }

// TWO PIPES
void	setup_commands(t_command *commands)
{
	// ls -l | grep "d" | wc -l
	commands[0].args = malloc(sizeof(char *) * 3);
	commands[0].args[0] = strdup("ls");
	commands[0].args[1] = strdup("-l");
	commands[0].args[2] = NULL;
	commands[0].infile = NULL;
	commands[0].outfile = NULL;
	commands[0].append_out = 0;
	commands[1].args = malloc(sizeof(char *) * 3);
	commands[1].args[0] = strdup("grep");
	commands[1].args[1] = strdup("d");
	commands[1].args[2] = NULL;
	commands[1].infile = NULL;
	commands[1].outfile = NULL;
	commands[1].append_out = 0;
	commands[2].args = malloc(sizeof(char *) * 3);
	commands[2].args[0] = strdup("wc");
	commands[2].args[1] = strdup("-l");
	commands[2].args[2] = NULL;
	commands[2].infile = NULL;
	commands[2].outfile = NULL;
	commands[2].append_out = 0;
}
// void	setup_commands(t_command *commands)
// {
// 	commands[0].args = malloc(sizeof(char *) * 4);
// 	commands[0].args[0] = strdup("unset");
// 	commands[0].args[1] = strdup("VAR1");
// 	commands[0].args[2] = strdup("VAR2");
// 	commands[0].args[3] = NULL;
// 	commands[0].infile = NULL;
// 	commands[0].outfile = NULL;
// 	commands[0].append_out = 0;
// }

// multiple pipes

int	main(void)
{
	t_env_vars	*env_vars;
	t_command	*commands;
	char		**env_array;
	t_env_vars	*path_var;
	t_env_vars	*home_var;
	char		full_path[PATH_MAX];

	env_vars = NULL;
	int num_commands = 3; // For ls | grep | wc
	// 1. Create minimal environment
	path_var = malloc(sizeof(t_env_vars));
	path_var->key = strdup("PATH");
	path_var->value = strdup("/bin:/usr/bin:/usr/local/bin");
	path_var->next = NULL;
	home_var = malloc(sizeof(t_env_vars));
	home_var->key = strdup("HOME");
	home_var->value = strdup("/Users/grace");
	home_var->next = path_var;
	env_vars = home_var;
	// 2. Setup pipeline commands
	commands = malloc(sizeof(t_command) * num_commands);
	setup_commands(commands);
	// 3. Resolve command paths
	for (int i = 0; i < num_commands; i++)
	{
		if (!commands[i].full_path)
		{ // Only resolve if not builtin
			resolve_command_full_path(env_vars, commands[i].args[0], full_path);
			if (full_path[0] != '\0')
			{
				commands[i].full_path = strdup(full_path);
			}
		}
	}
	// 4. Convert environment to array
	env_array = convert_env_to_array(env_vars);
	// 5. Execute the pipeline
	execute_pipes(commands, num_commands, env_array);
	// 6. Cleanup
	for (int i = 0; i < num_commands; i++)
	{
		for (int j = 0; commands[i].args[j]; j++)
			free(commands[i].args[j]);
		free(commands[i].args);
		if (commands[i].full_path)
			free(commands[i].full_path);
	}
	free(commands);
	free_env_vars(env_vars);
	free(env_array);
	return (0);
}

// check export main
// int	main(void)
// {
// 	char		**env_array;
// 	int			exit_code;
// 	t_command	*commands;
// 	int			num_commands;
// 	char		*args1[] = {"export", "VAR1=value1", NULL};
// 	char		*args2[] = {"export", "VAR2=value2", NULL};

// 	t_env_vars *env_vars = NULL; // Start with empty environment
// 	num_commands = 1;
// 	// 1. Initialize environment from actual environment variables
// 	initialize_env_list(&env_vars);
// 	// 2. Setup command(s)
// 	// 3. Resolve command path if needed
// 	ft_export(&env_vars, args1);
// 	ft_export(&env_vars, args2);
// 	printf("Before unset:\n");
// 	print_env_vars(env_vars);
// 	commands = malloc(sizeof(t_command) * num_commands);
// 	setup_commands(commands); // Your existing command setup
// 	resolve_all_command_paths(env_vars, commands, num_commands);
// 	// 5. Execute command
// 	printf("Running unset builtin for key: %s\n", commands[0].args[1]);
// 	exit_code = execute_builtin(&commands[0], &env_vars);
// 	if (exit_code == 2) // Not a builtin
// 	{
// 		env_array = convert_env_to_array(env_vars);
// 		execute_pipes(commands, num_commands, env_array);
// 		free_env_array(env_array);
// 	}
// 	printf("after unset:\n");
// 	print_env_vars(env_vars);
// 	// CHECK EXPORT DONT KNOW WHY THIS ISNT WORKING CAN SEE IN ENV
// 	// t_env_vars *node = get_env_node(env_vars, "MYVAR");
// 	//     if (node && strcmp(node->value, "test_value") == 0) {
// 	//     printf("✅ Export worked!\n");
// 	// }
// 	// else {
// 	//     printf("❌ Export failed\n");
// 	// }
// 	// 7. Cleanup
// 	free_env_vars(env_vars);
// 	return (exit_code);
// }

// TEST FOR CD NEED TO PRINT BEFORE AND AFTER PATH TO PROVE
// int	main(void)
// {
// 	t_env_vars	*home_var;
// 	t_env_vars	*env_vars;
// 	int			num_commands;
// 	t_command	*commands;
// 	char		full_path[PATH_MAX];
// 	char		current_dir[PATH_MAX];
// 	int			exit_code;
// 	char		**env_array;

// 	// 1. Create a mock envir lst
// 	home_var = malloc(sizeof(t_env_vars));
// 	home_var->key = strdup("HOME");
// 	home_var->value = strdup("/Users/grace");
// 	home_var->next = NULL;
// 	env_vars = malloc(sizeof(t_env_vars));
// 	env_vars->key = strdup("PATH");
// 	env_vars->value = strdup("/bin:/usr/bin:/usr/local/bin");
// 	env_vars->next = home_var;
// 	num_commands = 1;
// 	commands = malloc(sizeof(t_command) * num_commands);
// 	setup_commands(commands);
// 	if (ft_strcmp(commands[0].args[0], "pwd") != 0)
// 	{ // Only resolve for non-builtins
// 		resolve_command_full_path(env_vars, commands[0].args[0], full_path);
// 		if (full_path[0] != '\0')
// 		{
// 			commands[0].full_path = strdup(full_path);
// 		}
// 	}
// 	// 4. Exec builitins
// 	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
// 	{
// 		printf("Current Directory (Before cd): %s\n", current_dir);
// 	}
// 	else
// 	{
// 		perror("getcwd");
// 	}
// 	exit_code = execute_builtin(&commands[0], env_vars);
// 	printf("--- After execute_builtin ---\n");
// 	printf("Exit code from execute_builtin: %d\n", exit_code);
// 	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
// 	{
// 		printf("Current Directory (After cd): %s\n", current_dir);
// 	}
// 	else
// 	{
// 		perror("getcwd");
// 	}
// 	// exec pipes
// 	if (exit_code == 2)
// 	{ // Not a builtin, use execve
// 		env_array = convert_env_to_array(env_vars);
// 		exit_code = execute_builtin(commands, env_vars);
// 		// NEED TO CAPTURE EXIT CODE FROM BELOW TOO!!
// 		execute_pipes(commands, num_commands, env_array);
// 		free(env_array);
// 	}
// 	printf("exit_code: %i", exit_code);
// 	// free everythihg in reality
// 	return (exit_code);
// }
