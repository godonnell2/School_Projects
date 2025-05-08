// cc -lreadline  REMEMBER DUH
/*
 cc -Wall -Wextra -g -I$(brew --prefix readline)/include -L$(brew --prefix readline)/lib -lreadline heredoc.c
   */
/*
You want Ctrl+C to not terminate the shell, but instead interrupt the input — ✅
Ctrl+C (SIGINT) should interrupt the heredoc, print a newline,
 and return to the shell prompt.

Ctrl+D should act like EOF — this is already handled by readline()
returning NULL.

A SIGINT is sent to the process.

If you don't handle it, the default is: program is terminated.

If you do handle it (like you're doing), your signal handler is called.

The shell should not exit when SIGINT is received during heredoc input.

After heredoc ends, restore the original signal behavior.

When multiple threads call printf simultaneously, the locks prevent interleaved output

The lock protects both the buffer and the formatting state

Userspace Complexity:

printf handles formatting, buffering, locale settings, etc.

All these features require synchronization
where as write
Goes straight to kernel without intermediate buffers
printf with \n doesnt buffer!!!

r signal handler should do only this:

Set a global volatile sig_atomic_t flag to indicate a signal arrived

Nothing else
Then in your main program loop:

Regularly check the flag

Perform all actual signal response work there (outside the handler)
The child is still running and stuck in the heredoc loop, even after the parent moves on and returns to the prompt.

Parent sees child exit, but that's likely from an earlier child, or it didn't actually wait correctly (possibly due to overlapping file descriptors).

You're seeing readline prompts from the previous child still running, and they’re interfering with the next shell session.
*/
// #include "minishell.h"
#include <stdio.h> //has to come before readline 
#include <readline/readline.h>
#include <readline/history.h> //rl_replace_line
#include <signal.h>
#include <errno.h>      // For errno and EINTR
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#define READ 0
#define WRITE 1
#define STDIN 0
#define INITIAL_SIZE 32



volatile sig_atomic_t signal_received;

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char *mini_getline(void)
{
    size_t capacity = INITIAL_SIZE;
    size_t len = 0;
    char *line = malloc(capacity);
    char buf;
    ssize_t r;

    if (!line) {
        return NULL;
    }

    while ((r = read(STDIN_FILENO, &buf, 1)) > 0) {
        if (buf == '\n') {
            break;
        }

        // Check if we need more space
        if (len + 1 >= capacity) {
            capacity *= 2;
            char *new_line = malloc(capacity);
            if (!new_line) {
                free(line);
                return NULL;
            }
            memcpy(new_line, line, len);
            free(line);
            line = new_line;
        }

        line[len++] = buf;
    }

    // Handle signal interruption
    if (r == -1 && errno == EINTR) {
        free(line);
		 signal_received = 1; 
		  return NULL; 
        //return strdup(""); // Return empty string on Ctrl+C
    }

    // Handle EOF or error
    if (r <= 0 && len == 0) {
        free(line);
        return NULL;
    }

    // Null-terminate the string
    line[len] = '\0';
    return line;
}

// char *mini_getline(void)
// {
// 	char *line = NULL;
// 	char buf;
// 	size_t len = 0;
// 	ssize_t r;

// 	while ((r = read(STDIN_FILENO, &buf, 1)) > 0)
// 	{
// 		if (buf == '\n')
// 			break;
// 		char *new_line = realloc(line, len + 2);
// 		if (!new_line)
// 		{
// 			free(line);
// 			return NULL;
// 		}
// 		line = new_line;
// 		line[len++] = buf;
// 	}

// 	if (r == -1 && errno == EINTR)
// 	{
// 		free(line);
// 		return strdup(""); // Don't exit on Ctrl+C
// 	}

// 	if (r <= 0 && len == 0)
// 		return NULL;

// 	if (line)
// 		line[len] = '\0';
// 	return line;
// }

void sigint_handler(int sig)
{
	(void)sig;

	signal_received = 1;
}
// USE MORE complicated prototype whcih is the SAhandler
// sets up the conditions to be ready to receive a signal
void setup_signals(void)
{
	struct sigaction sa_int;
	// this is the struct to handle not quitting on ctrlbackslash
	struct sigaction sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	// Clears the signal mask (no signals blocked during handler execution)
	sigemptyset(&sa_int.sa_mask);
	// Actually installs the handler for SIGINT (Ctrl+C)
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void suppress_control_echo(void)
{
	struct termios term;
	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void restore_control_echo(void)
{
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag |= ECHOCTL;  // Re-enable Ctrl character echo
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
}

//Set SIGINT to default behavior, so Ctrl+C kills the child immediately.
//Also ignore SIGQUIT, just like bash.
void handle_signal_in_heredoc(void)
{
    // Temporary signal ignoring for the child process during heredoc
    struct sigaction sa_int;
   struct sigaction sa_quit;

	sa_int.sa_handler = SIG_DFL;  // Ctrl+C should kill heredoc input
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN; // Ignore Ctrl+backslash
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}


int ft_heredoc(const char *delimiter)
{
	
    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process
        close(fds[0]);
        handle_signal_in_heredoc(); // Ignore signals during heredoc process
        suppress_control_echo();
        
        while (1)
        {
            char *line;
            write(STDOUT_FILENO, "> ", 2);
            line = mini_getline();
            if (!line)
			{
				if (signal_received) 
				{
                // Clean exit on signal
                	restore_control_echo();
                	close(fds[1]);
                	exit(EXIT_SUCCESS);  // Exit normally rather than by signal
            	}
				break;
			}
                
            if (ft_strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            write(fds[1], line, ft_strlen(line));
            write(fds[1], "\n", 1);
            free(line);
        }

        restore_control_echo();
        close(fds[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        close(fds[1]);
        int status;
        waitpid(pid, &status, 0); // Wait for child to exit
        restore_control_echo();
		
//WIFEXITED(status) if a child exited normally
        
		//below if a child was exited using a signal
	// if (WIFSIGNALED(status))
	// {
	// 	close(fds[0]);
	// 	return -1;  // signal killed heredoc
	// }
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) 
		{
    	return fds[0];  // child succeeded
		}
	}
        close(fds[0]);
        return -1;
}


int main(void)
{
	int in_heredoc= 0;
	setup_signals();
	suppress_control_echo();
	while (1)
	{
		if (signal_received) 
		{
            signal_received = 0;
            // Only print newline if we're not in heredoc
            if (!in_heredoc) 
			{
                write(STDOUT_FILENO, "\n", 1);
            }
		}
		write(STDOUT_FILENO, "graceoutershell: ", 17);
		char *input = mini_getline();
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}

		if (ft_strcmp(input, "heredoc") == 0)
		{
			write(STDOUT_FILENO, "Main: Calling ft_heredoc\n", 26);
			in_heredoc = 1;
			int fd = ft_heredoc("EOF");
			in_heredoc = 0;
			
				suppress_control_echo();  // <- THIS prevents ^\ from echoing after ctrl c in heredoc was producing this 
			if (fd == -1)
			{
				write(STDOUT_FILENO, "Main: Heredoc failed", 21);
			}
			else
			{
				write(STDOUT_FILENO, "Main: Reading from heredoc_fd\n", 31);
				char buf[1024];
				int n;
				while ((n = read(fd, buf, sizeof(buf))) > 0)
					write(STDOUT_FILENO, buf, n);
				close(fd);
				write(STDOUT_FILENO, "Main: heredoc_fd closed\n", 25);
			}
		}
		free(input);
	}
	return 0;
}

/*

// TEST MAX HERE DOC 64 KIB
// ALSO NEED TO REMEMBER TO CLOSE READ END AFTER DUP2 in next fork


// int	ft_heredoc(char *endoffile)
// {
// 	int		pipe_fd[2];
// 	char	*line;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("heredoc:pipe cretion");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if ((ft_strcmp(endoffile, line) == 0))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(pipe_fd[WRITE], line, ft_strlen(line));
// 		write(pipe_fd[WRITE], "\n", 1);
// 		free(line);
// 	}
// 	close(pipe_fd[WRITE]);
// 	return (pipe_fd[READ]);
// }

◦ << should be given a delimiter,
 then read the input until a line containing the delimiter is seen.
 However, it doesn’t have to update the history!

cat << EOF
hello
world
EOF

echo -e "hello\nworld" | cat

cc heredoc.c  -lreadline


🧠 What Is the Kernel?
The kernel is the core part of an operating system.
 It's the bridge between your programs and your computer’s hardware.
 It runs in a privileged mode called kernel space, which has direct
  access to memory, CPU, devices, and more.

When your code does something like:

Open a file

Create a process

Allocate memory

Send network data

...you’re not doing those things directly. You're asking the kernel to do them
 for you — through a system call (like open(), read(), execve()).

🛠️ What About File Descriptors?
When you open a file or run a command, the kernel assigns a file descriptor
 — a small number (like 0, 1, 2,
	3...) — that your process can use to refer to that file, pipe, or device.

For example:

0 = stdin (keyboard)

1 = stdout (screen)

2 = stderr (errors)

When you run a command with > out.txt, your shell asks the kernel to:

Open out.txt (get a new file descriptor, say fd 3)

Redirect stdout (fd 1) to point to fd 3

The kernel manages these descriptors and makes sure each process
 gets its own isolated set.

🔐 Why It Matters for Your Shell
When you implement redirections or pipes, your shell sets up file
 descriptors and then asks the kernel to handle the actual execution.
 You’re writing the user-space logic that controls how the kernel should
 route input/output.


*/