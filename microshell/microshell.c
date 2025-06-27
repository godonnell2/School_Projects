

/* Custom error message writer to STDERR
 * @param str: Base error message
 * @param arg: Optional argument to append to message */
#include "microshell.h"

void ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}

void ft_fatal_error(int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd2("error: fatal", NULL);
		exit(1);
	}
}

/* Execute command in child process
 * @param argv: Command and arguments array
 * @param i: Index where command ends (at ; or |)
 * @param tmp_fd: Input file descriptor from previous pipe
 * @param env: Environment variables */
void ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
	//overwrite ; or | or NULL with NULL to use the array as input for execve.
	//we are here in the child so it has no impact in the parent process.

	argv[i] = NULL; // Terminate command array for execve
	// Redirect input
	ft_fatal_error(dup2(tmp_fd, STDIN_FILENO));  // Added error check
	close(tmp_fd);
	execve(argv[0], argv, env);
	ft_putstr_fd2("error: cannot execute ", argv[0]);
	exit(1);
}

int	main(int argc, char *argv[], char *env[])
{
	int		i;
	int 	fd[2]; // Pipe file descriptors [read, write]
	int 	tmp_fd;  // Stores input source for next command
	pid_t 	pid;

	(void)argc;
	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	ft_fatal_error(tmp_fd);  // Initial dup check

	// Process commands until end of arguments
	while (argv[i] && argv[i + 1]) //check if the end is reached
	{
		// Advance to next command group
		argv = &argv[i + 1];	//the new argv start after the ; or |
		i = 0;

		// Find command boundaries: ; | or end of args
		//count until we have all informations to execute the next child;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;

		// Handle built-in cd command
		if (strcmp(argv[0], "cd") == 0) //cd
		{
			if (i != 2) // cd + path = 2 arguments
				ft_putstr_fd2("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]	);
		}
		// Execute regular command ending with ; or EOL
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0)) //exec in stdout
		{
			pid = fork();  // Store fork result
			ft_fatal_error(pid);
			if (pid == 0) // Child process
				ft_execute(argv, i, tmp_fd, env);
			else // Parent process
			{
				close(tmp_fd);
				// Wait for all child processes to complete
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO); // Reset input for next command
				ft_fatal_error(tmp_fd);  // Check dup after wait
			}
		}
		// Handle pipe operation
		else if(i != 0 && strcmp(argv[i], "|") == 0) //pipe
		{
			ft_fatal_error(pipe(fd));  // Pipe error check
			pid = fork();  // Store fork result
			ft_fatal_error(pid);
			if (pid == 0) // Child writes to pipe
			{
				ft_fatal_error(dup2(fd[1], STDOUT_FILENO));  // Output redirection check
				close(fd[0]);
				close(fd[1]);
				ft_execute(argv, i, tmp_fd, env);
			}
			else  // Parent prepares for next command
			{
				close(fd[1]);    // Close write end
				close(tmp_fd);  // Close previous input
				tmp_fd = fd[0]; // Next command reads from pipe
			}
		}
	}
	close(tmp_fd);
	return (0);
}