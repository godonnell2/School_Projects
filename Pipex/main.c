/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:27:24 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 18:27:25 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
returns a pid_t, which is the process ID of the created child process
3 params:
t_data *data: pntr to a struct that holds process IDs and file descriptors.
char *argv[]: An array of command-line arguments.
char *envp[]: An array of environment variables.
The first child writes data to the pipe (via pipe_fd[WRITE_END]).
It doesn't need to read from the pipe (pipe_fd[READ_END]).
In the child process (where data->pid1 == 0),
the child will be writing data to the pipe (via STDOUT_FILENO),
and it does not need to read from the pipe.
Closing the read end of the pipe

dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) effectively redirects the
standard output of the child process to the write end of the pipe.
This allows the child to send its output to the parent process through the
 pipe.

dup2(data->in_fd, STDIN_FILENO)
after this call, any input that would normally come from the terminal (standard
input) will instead be read from the file associated with data->in_fd. This
means that any function that reads from standard input (e.g., scanf, getchar,
 etc.) will now read from the specified file instead of the terminal.

 (execlp seems to be a utility to use the PATH to find the program,
 because "raw" exec requires the full path
 Execv is very similar except it doesn't use variable length arguments
*/

pid_t	first_child(t_data *data, char **av, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		err_case("fork for first child failed", data);
	if (data->pid1 == 0)
	{
		data->input_fd = open(av[1], O_RDONLY);
		if (data->input_fd < 0)
			err_case("failure to open input file", data);
		close(data->pipe_fd[READ_END]);
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
			err_case("dup2 stdoutput kid to writeend pipe,dad process", data);
		close(data->pipe_fd[WRITE_END]);
		if (dup2(data->input_fd, STDIN_FILENO) < 0)
			err_case("dup2 stdin terminal to file w/ data->in_fd", data);
		close(data->input_fd);
		data->args_cmds = ft_split(av[2], ' ');
		data->cmd = find_fullpath(envp, data->args_cmds[0]);
		execve(data->cmd, data->args_cmds, envp);
	}
	return (data->pid1);
}

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
data->pipe_fd[READ_END].
 Why Close WRITE_END?
a) Avoid Resource Waste:
The second child does not need the WRITE_END of the pipe.
Keeping it open unnecessarily consumes system resources, as the operating
 system maintains open file descriptors.
b) Allow Proper EOF Detection:
When the first child process writes to the pipe and closes its WRITE_END,
 the second child detects the end-of-file (EOF) on the pipe when it finishes
  reading.
If the WRITE_END is left open in the second child:
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

 if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
redirect standard input (stdin) of the current process
(typically a child process)
to read from the read end of a pipe
*/

pid_t	second_child(t_data *data, int ac, char **av, char **envp)
{
	data->pid2 = fork();
	if (data->pid1 < 0)
		err_case("fork for second child failed", data);
	if (data->pid2 == 0)
	{
		data->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (data->output_fd < 0)
			err_case("failed to open output file", data);
		if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
			err_case("dup2 stdin current child process to readend pipe", data);
		close(data->pipe_fd[READ_END]);
		if (dup2(data->output_fd, STDOUT_FILENO) < 0)
			err_case("dup2 stdout currkid proc write file instead term", data);
		close(data->output_fd);
		data->args_cmds = ft_split(av[3], ' ');
		data->cmd = cmd_path(envp, data->args_cmds[0]);
		execve(data->cmd, data->args_cmds, envp);
	}
	return (data->pid2);
}

/*
The parent process creates the pipe and spawns two child processes
(first_child and second_children). Each child has a specific
 responsibility regarding the pipe:

The first child writes data into the pipe.
The second child reads data from the pipe.
The parent itself doesn’t perform any read or write operations on the pipe,
 so it needs to close both ends of the pipe after forking the children.
we are in the parent right now after we fork

*/
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 5)
		print_usage();
	init_data(&data);
	if (pipe(data->pipe_fd) < 0)
		err_case("pipe FAILED", data);
	if (first_child(data, av, envp) < 0)
		err_case("fork FAILED for first child", data);
	if (second_children(data, ac, av, envp) < 0)
		err_case("fork FAILED for second child", data);
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
	free(data);
	return (0);
}
