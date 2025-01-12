/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:27:24 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/12 20:45:27 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	first_child(t_data *data, char **av, char **envp)
{
	char	buff[SPLIT_BUFF_SIZE];
	char	**args_cmds;
	char	cmd[PATH_MAX];

	args_cmds = ft_split_buff(av[2], ' ', buff);
	find_fullpath(envp, args_cmds[0], cmd);
	if (cmd[0] == '\0')
		err_case("Command not found", data);
	data->input_fd = open(av[1], O_RDONLY);
	if (data->input_fd < 0)
		err_case("failure to open input file", data);
	data->pid1 = fork();
	if (data->pid1 < 0)
		err_case("fork for first child failed", data);
	if (data->pid1 != 0)
		return (data->pid1);
	if (dup2(data->pipe_fd[WRITE], OUT) < 0 || dup2(data->input_fd, IN) < 0)
		err_case("dup2 failed", data);
	close(data->pipe_fd[WRITE]);
	close(data->input_fd);
	execve(cmd, args_cmds, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

pid_t	second_child(t_data *data, int ac, char **av, char **envp)
{
	char	buff[SPLIT_BUFF_SIZE];
	char	**args_cmd;
	char	cmd[PATH_MAX];

	close(data->pipe_fd[WRITE]);
	args_cmd = ft_split_buff(av[3], ' ', buff);
	find_fullpath(envp, args_cmd[0], cmd);
	if (cmd[0] == '\0')
		err_case("Command not found", data);
	data->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->output_fd < 0)
		err_case("failed to open output file", data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		err_case("fork for second child failed", data);
	if (data->pid2 != 0)
		return (data->pid2);
	if (dup2(data->pipe_fd[READ], IN) < 0 || dup2(data->output_fd, OUT) < 0)
		err_case("dup2 failed", data);
	close(data->pipe_fd[READ]);
	close(data->output_fd);
	execve(cmd, args_cmd, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
		print_usage();
	data = init_data();
	if (pipe(data.pipe_fd) < 0)
		err_case("pipe FAILED", &data);
	if (first_child(&data, av, envp) < 0)
		err_case("fork FAILED for first child", &data);
	if (second_child(&data, ac, av, envp) < 0)
		err_case("fork FAILED for second child", &data);
	close(data.pipe_fd[READ]);
	close(data.pipe_fd[WRITE]);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	return (0);
}

/*
returns a pid_t, which is the process ID of the created child process
3 params:
t_data *data: pntr to a struct that holds process IDs and file descriptors.
char *argv[]: An array of command-line arguments.
char *envp[]: An array of environment variables.
The first child writes data to the pipe (via pipe_fd[WRITE_END]).
It doesn't need to read from the pipe (pipe_fd[READ]).
In the child process (where data->pid1 == 0),
the child will be writing data to the pipe (via STDOUT_FILENO),
and it does not need to read from the pipe.
Closing the read end of the pipe

dup2(data->pipe_fd[WRITE], STDOUT_FILENO) effectively redirects the
standard output of the child process to the write end of the pipe.
This allows the child to send its output to the parent process through the
 pipe.

dup2(data->in_fd, STDIN)
after this call, any input that would normally come from the terminal (standard
input) will instead be read from the file associated with data->in_fd. This
means that any function that reads from standard input (e.g., scanf, getchar,
 etc.) will now read from the specified file instead of the terminal.

 (execlp seems to be a utility to use the PATH to find the program,
 because "raw" exec requires the full path
 Execv is very similar except it doesn't use variable length arguments
*/

/*
The parent process creates the pipe and spawns two child processes
(first_child and second_child). Each child has a specific
 responsibility regarding the pipe:

The first child writes data into the pipe.
The second child reads data from the pipe.
The parent itself doesn’t perform any read or write operations on the pipe,
 so it needs to close both ends of the pipe after forking the children.
we are in the parent right now after we fork

*/

/*
When a process is created using fork(), it inherits all open file descriptors
 from its parent process. This means that both the parent and the child will
 have access to the same pipe file descriptors.
To ensure that the second child process only reads from the pipe and does not
attempt to write to it, you need to close the write end of the pipe in the
second child process.
The second child process is responsible for reading from the pipe and writing
 the output to the specified file.
The second child does not write to the pipe; it only reads from it using
data->pipe_fd[READ].
 Why Close WRITE?
a) Avoid Resource Waste:
The second child does not need the WRITE of the pipe.
Keeping it open unnecessarily consumes system resources, as the operating
 system maintains open file descriptors.
b) Allow Proper EOF Detection:
When the first child process writes to the pipe and closes its WRITE,
 the second child detects the end-of-file (EOF) on the pipe when it finishes
  reading.
If the WRITE is left open in the second child:
The pipe remains open for writing, even though the second child isn’t using it.
This prevents the second child from detecting EOF, as the operating system
 assumes the pipe is still active for writing.
 O_RDWR: Open the file for both reading and writing.
O_CREAT: Create the file if it does not already exist.
If the file is created, it will be empty.
O_TRUNC: If the file already exists, truncate it to zero
length (i.e., clear its contents) when opened.
The owner of the file can read and write (6 = read + write).
The group can read (4 = read).
Others can read (4 = read).

 if (dup2(data->pipe_fd[READ], STDIN) < 0)
redirect standard input (stdin) of the current process
(typically a child process)
to read from the read end of a pipe

The leading 0 in 0644 is a notation in C (and many other programming languages)
indicating that the number is written in octal (base 8) rather than decimal
(base 10)
→ Read and Write permissions for the owner (4 + 2 = 6).
4 → Read-only permissions for the group.
4 → Read-only permissions for others.
*/