#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define READ 0
#define WRITE 1
#define STDIN 0

volatile sig_atomic_t signal_received;

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
//error message data if sigaction 
void sigint_handler(int sig)
{
    (void)sig;

    signal_received = 1;

}
//USE MORE complicated prototype whcih is the SAhandler 
//sets up the conditions to be ready to receive a signal 
void setup_signals(void)
{
	struct sigaction sa_int;
	//this is the struct to handle not quitting on ctrlbackslash
	struct sigaction sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_SIGINFO;
	//Clears the signal mask (no signals blocked during handler execution)
	sigemptyset(&sa_int.sa_mask);
//Actually installs the handler for SIGINT (Ctrl+C)
	 sigaction(SIGINT, &sa_int, NULL);

	 sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	
}



int ft_heredoc(char *endoffile)
{
    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("heredoc:pipe creation");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("heredoc:fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process: Ignore Ctrl+C or handle it cleanly
        signal(SIGINT, SIG_IGN);  // Option A: Ignore
        // OR:
        // struct sigaction sa_child = {0};
        // sa_child.sa_handler = SIG_DFL;  // Option B: Terminate
        // sigaction(SIGINT, &sa_child, NULL);

        close(fds[READ]);
        char *line;
        while (1)
        {
            line = readline("> ");
            if (!line || signal_received == 1)
            {
                free(line);
                break;
            }
            if (ft_strcmp(endoffile, line) == 0)
            {
                free(line);
                break;
            }
            write(fds[WRITE], line, ft_strlen(line));
            write(fds[WRITE], "\n", 1);
            free(line);
        }
        close(fds[WRITE]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fds[WRITE]);
        int status;
        waitpid(pid, &status, 0);  // Wait for child to finish
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
        {
            return fds[READ];  // Success
        }
        close(fds[READ]);
        return -1;  // Heredoc failed
    }
}

int	main(void)
{
	setup_signals();

	while (1)
	{
		if (signal_received == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		signal_received = 0;
	}
		char *input = readline("minioutershellprompt: ");
		if (!input)
		{
			if (signal_received != 2)
				write(STDOUT_FILENO, "exit\n", 5);
			break;
		}

		if (ft_strcmp(input, "heredoc") == 0)
		{
			int heredoc_fd = ft_heredoc("EOF");
			
		 
			// Simulate command reading from heredoc
			char buf[1024];
			ssize_t n;
			while ((n = read(heredoc_fd, buf, sizeof(buf))) > 0)
				write(STDOUT_FILENO, buf, n);
			close(heredoc_fd);
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		free(input);
	}
	return 0;
}
