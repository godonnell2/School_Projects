// changed to proper strdup now that minishell.h but need to check again 

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
#include "minishell.h"
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

//, using a pipe is better for performance, 
//especially with large heredoc content, as it avoids writing to disk.

volatile sig_atomic_t signal_received;



// size_t ft_strlen(const char *str)
// {
// 	size_t len;

// 	len = 0;
// 	while (str[len] != '\0')
// 	{
// 		len++;
// 	}
// 	return (len);
// }
//NEED CUSTOM IMPLEMENTATION OF MEMCPY 

void	*my_memcpy(void *dest, const void *src, size_t n)
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

char *mini_getline(void)
{
	char *line = NULL;
	char buf;
	size_t len = 0;
	ssize_t r;

	while ((r = read(STDIN_FILENO, &buf, 1)) > 0)
	{
		if (buf == '\n')
			break;
		char *new_line = malloc(len+2);
		if (!new_line)
		{
			free(line);
			return NULL;
		}
        if (line)
        {
            my_memcpy(new_line, line, len);
            free(line);
        }
		line = new_line;
		line[len++] = buf;
	}
// so ctrl c normally exits but we are saying instead
// lets return something that is non null (so as to not trigger EOF)
// EINTER is the error code for interrupted system call

	if (r == -1 && errno == EINTR)
	{
		free(line);
		return ft_strdup(""); // Don't exit on Ctrl+C
	}

	if (r <= 0 && len == 0)
		return NULL;

	if (line)
		line[len] = '\0';
	return line;
}

void sigint_handler(int sig)
{
	(void)sig;

	signal_received = 1;
}

void setup_signals(void)
{
	struct sigaction sa_int;
	// this is the struct to handle not quitting on ctrl+ 
	struct sigaction sa_quit;
	//normally ctrl c exits we are saying hey listen to us instead so we can handle it 
	// ie create a new prompt instead in outer shell 
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	// Clears the signal mask (no signals blocked during handler execution)
	sigemptyset(&sa_int.sa_mask);
	// Actually installs the handler for SIGINT (Ctrl+C)
	sigaction(SIGINT, &sa_int, NULL);

	//normally ctrl backslash quits shell ( and dumps a core file for debugging) we are saying actually 
	// just ignore it !  SIG_IGN =A special macro meaning "ignore this signal."
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// termios is a structure that stores terminal attributes
	//struct termios controls terminal I/O behavior (input, output, modes, special chars).
	//is a data structure used in Unix-like systems to configure and control terminal (TTY) behavior. 
	//It defines how input and output are processed by the terminal driver. 
	// there are a million flags not going to go into all of them 
	// tcgetattr =fn that retrieves the curr terminal attributes (like echo behavior, input modes, etc.) 
	//into the term struct.
	//== 0 is check for success ie we got the atts
	// ECHOCTL is a flag that controls whether control characters are echoed
	//the tilde (~) is the bitwise NOT operator in C. It flips all the bits of a value. 
	//ECHOCTL is a Bitmask Flag
	// the tilde inverts the bits effectively turning off the ECHOCTL flag
	//The &= (bitwise AND + assignment) combines the current c_lflag with the inverted mask:
	// c_lflag &= ~ECHOCTL
	//This means: "Keep all the bits in c_lflag the same, except for ECHOCTL, which should be turned off."
	//Example:
	// c_lflag:  01010101  (Current terminal settings)
	// ECHOCTL:  00000100  (Only the 3rd bit is set)
	//~ECHOCTL: 11111011  (All bits flipped, 3rd bit is now 0)
	// 	c_lflag:   01010101  
	// & ~ECHOCTL:11111011  
	// -------------------
	// Result:    01010001  (3rd bit is now 0, others unchanged)

//Without ~:
//term.c_lflag &= ECHOCTL would turn off all bits except ECHOCTL (likely breaking the terminal).
//he termios man page explicitly states that ECHOCTL is a flag in c_lflag.
//The definition of ECHOCTL is found in termios.h under the c_lflag flags:
// c_lflag controls local terminal behavior (how the terminal processes input/output).
// c_iflag	Input processing (e.g., converting \r to \n, flow control).
// c_oflag	Output processing (e.g., converting \n to \r\n).
// c_cflag	Hardware control (baud rate, parity, stop bits, etc.).
// c_lflag	Local behavior (echo, line buffering, signals, etc.).
void suppress_control_echo(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	//ie we are not in terminal mode (ie stdin is not a terminal) we can just ignore it eg doing a pipe or redirect
	
	else
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
}

// Re-enable Ctrl character echo
void restore_control_echo(void)
{
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag |= ECHOCTL;  
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
                break;
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
       // restore_control_echo();

        //WIFEXITED(status) if a child exited normally
        
		//below if a child was exited using a signal
	if (WIFSIGNALED(status))
	{
	    write(STDOUT_FILENO, "\n", 1);  // Ctrl+C newline
	    close(fds[0]);
	    return -1;  
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) 
	{
        return fds[0];  // child succeeded
	}
    close(fds[0]);
    return -1;
    }
}

/*
int main(void)
{
	setup_signals();
    suppress_control_echo();
	while (1)
	{
		if (signal_received)
		{
			//so basically in the mainshell when get the signal you have to print a new prompt
			write(STDOUT_FILENO, "\n", 1);
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
			signal_received = 0;
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
			int fd = ft_heredoc("EOF");
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
*/