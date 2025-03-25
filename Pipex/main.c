/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:27:24 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/25 18:21:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_input_and_commands(t_data *data, char **av, char **envp)
{
	data->input_fd = open(av[1], O_RDONLY);
	if (data->input_fd < 0)
		err_case_perror(data, av, 1);
	data->cmd1_args = ft_split_buff(av[2], ' ', data->buff);
	if (data->cmd1_args[0] == NULL)
		err_case_cmd(data, av, 2);
	resolve_command_full_path(envp, data->cmd1_args[0], data->cmd1_fullpath);
	if (data->cmd1_fullpath[0] == '\0')
		err_case_cmd(data, av, 2);
	data->cmd2_args = ft_split_buff(av[3], ' ', data->buff_two);
	if (data->cmd2_args[0] == NULL)
		err_case_cmd(data, av, 3);
	resolve_command_full_path(envp, data->cmd2_args[0], data->cmd2_fullpath);
	if (data->cmd2_fullpath[0] == '\0')
		err_case_cmd(data, av, 3);
	return (1);
}

static void	handle_first_child(t_data *data, char **envp)
{
	  
    close(data->pipe_fd[WRITE]);
    if (data->input_fd != STDIN_FILENO) {
        if (dup2(data->input_fd, STDIN_FILENO) < 0) {
            perror("dup2 input_fd");
            exit(EXIT_FAILURE);
        }
        close(data->input_fd);
    }

    if (dup2(data->pipe_fd[WRITE], STDOUT_FILENO) < 0) {
        perror("dup2 pipe_fd");
        exit(EXIT_FAILURE);
    }
    close(data->pipe_fd[READ]);
		execve(data->cmd2_fullpath, data->cmd1_args, envp);
	perror("");
	exit(EXIT_FAILURE);
}

static void	handle_second_child(t_data *data, char **av, char **envp)
{
	data->output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output_fd < 0)
		err_case_perror(data, av, 4);
	if (dup2(data->pipe_fd[READ], IN) < 0 || dup2(data->output_fd, OUT) < 0)
		err_case(data, NULL);
	close(data->pipe_fd[READ]);
	close(data->output_fd);
	execve(data->cmd2_fullpath, data->cmd2_args, envp);
	perror("");
	exit(EXIT_FAILURE);
}

static void	create_pipes_and_forks(t_data *data, char **av, char **envp)
{
	if (pipe(data->pipe_fd) < 0)
		err_case(data, NULL);
	data->pid1 = fork();
	if (data->pid1 < 0)
		err_case(data, NULL);
	if (data->pid1 == 0)
		handle_first_child(data, envp);
	close(data->pipe_fd[WRITE]);
	data->pid2 = fork();
	if (data->pid2 < 0)
		err_case(data, NULL);
	if (data->pid2 == 0)
		handle_second_child(data, av, envp);
	close(data->pipe_fd[READ]);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
		print_usage();
	data = init_data();
	if (!validate_input_and_commands(&data, av, envp))
		return (1);
	create_pipes_and_forks(&data, av, envp);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	close_data(&data);
	return (0);
}

/*
When you pass 0 as the third argument to waitpid, it means that you are not
using any special options. The function will block (i.e., wait)
 until the specified child process (in this case, data.pid1) terminates.
*/

/*
<<<<<<< HEAD
=======
int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		exit_code;

	exit_code = 0;
	if (ac != 5)
		print_usage();
	data = init_data();
	if (!validate_input_and_commands(&data, av, envp))
	{
		return (1);
	}
	if (pipe(data.pipe_fd) < 0)
		err_case(&data, av);
	data.pid1 = fork();
	if (data.pid1 < 0)
		err_case(&data, av);
	if (data.pid1 == 0)
	{
		if (dup2(data.input_fd, IN) < 0 || dup2(data.pipe_fd[WRITE], OUT) < 0)
			err_case(&data, av);
		close(data.pipe_fd[READ]);
		close(data.pipe_fd[WRITE]);
		close(data.input_fd);
		execve(data.cmd1_fullpath, data.cmd1_args, envp);
		perror("");
		exit(EXIT_FAILURE);
	}my_printf2.c: OK!
ac - 1);
	data.pid2 = fork();
	if (data.pid2 < 0)
		err_case(&data, av);
	if (data.pid2 == 0)
	{
		if (dup2(data.pipe_fd[READ], IN) < 0 || dup2(data.output_fd, OUT) < 0)
			err_case(&data, av);
		close(data.pipe_fd[READ]);
		close(data.output_fd);
		execve(data.cmd2_fullpath, data.cmd2_args, envp);
		perror("");
		exit(EXIT_FAILURE);
	}
	close(data.pipe_fd[READ]);
	close(data.output_fd);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, &exit_code, 0);
	close_data(&data);
	return (exit_code);
}
*/

/*
>>>>>>> 40886d6f2ebf7de93f24aa94198ba32ae39266e2
ERROR ONE!!
valgrind --trace-children=yes --track-fds=yes ./pipex infile "" "" FIXED
valgrind --trace-children=yes --track-fds=yes ./pipex input.txt "cat" "" out
FIXED I THINK??!!!
maybe this is an issue with if data->pid != 0 return data->pid

ERROR TWO!!
valgrind --trace-children=yes --track-fds=yes ./pipex input.txt "cd" "wc -l" pwd
one extra open fd NOT SURE ABOUT THIS ONE

ERROR THREE
valgrind --trace-children=yes --track-fds=yes ./pipex input.txt "sleep 1"
"sleep 10" out
time ./pipex input.txt "sleep 2" "sleep 2" out
printf("fds input=%d pipe[0]=%d pipe[1]=%d\n", data.input_fd,
		data.pipe_fd[0], data.pipe_fd[1]);
Need to protect against no ENV

*/
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
The second child does not write to the waitpid(data.pid2, NULL, 0);
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
