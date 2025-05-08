#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

// Global variable to track signals in main shell
int signal_received = 0;

// Initial buffer size for mini_getline
#define INITIAL_SIZE 128


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

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
// Signal handler for main shell
void shell_sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nShell: SIGINT received\n", 23); // Debug message for SIGINT
    signal_received = 1; // Set flag to handle in the main loop
}

void sigquit_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "Quit: 3\n", 8);  // Custom Quit message
}
// // Signal handler for heredoc child process (Ctrl+C should terminate the heredoc)
// void heredoc_sigint_handler(int sig)
// {
//     (void)sig;
//     write(STDOUT_FILENO, "\nHeredoc: SIGINT received, exiting child\n", 39); // Debug message for SIGINT in heredoc
//     _exit(130);  // Exit heredoc child process with exit code 130 (Ctrl+C)
// }

// Set up signal handling for the main shell
void setup_signals(void)
{
    struct sigaction sa_int, sa_quit;

    // Main shell SIGINT handler (Ctrl+C)
    sa_int.sa_handler = shell_sigint_handler;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Ignore SIGQUIT (Ctrl+\) in the main shell
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

// Set signal handling for the heredoc child process
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


void restore_signal_handling(void)
{
    // Restore SIGINT to the default handler (to handle Ctrl+C properly outside heredoc)
    struct sigaction sa_int;
    sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    // Restore SIGQUIT to default (so Ctrl+\ behaves normally)
    struct sigaction sa_quit;
    sa_quit.sa_handler = SIG_DFL;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
// Suppress Ctrl+ characters in the terminal input (echo off for Ctrl characters)
void suppress_control_echo(void)
{
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
}

// Restore Ctrl+ character echo to the terminal
void restore_control_echo(void)
{
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag |= ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
}

// Function to read a line from stdin (handles signals and dynamic memory)
char *mini_getline(void)
{
    size_t capacity = INITIAL_SIZE;
    size_t len = 0;
    char *line = malloc(capacity);
    char buf;
    ssize_t r;

    if (!line)
    {
        write(STDOUT_FILENO, "mini_getline: Failed to allocate memory\n", 40);
        return NULL;
    }

    while ((r = read(STDIN_FILENO, &buf, 1)) > 0)
    {
        if (buf == '\n')
        {
            write(STDOUT_FILENO, "mini_getline: Newline detected, breaking loop\n", 47);
            break;
        }

        if (len + 1 >= capacity)
        {
            capacity *= 2;
            char *new_line = malloc(capacity);
            if (!new_line)
            {
                write(STDOUT_FILENO, "mini_getline: Failed to reallocate memory\n", 41);
                free(line);
                return NULL;
            }
            memcpy(new_line, line, len);
            free(line);
            line = new_line;
        }

        line[len++] = buf;
    }

    // Debug: Check for read error or signal interruption
    if (r == -1 && errno == EINTR)
    {
        write(STDOUT_FILENO, "mini_getline: Read interrupted by signal (EINTR)\n", 49);
        free(line);
        signal_received = 1;  // Set signal_received flag for main loop
        return NULL;  // Return NULL to indicate signal interruption
    }

    // Debug: Check for EOF or error with no data read
    if (r <= 0 && len == 0)
    {
        write(STDOUT_FILENO, "mini_getline: EOF or error with no input\n", 41);
        free(line);
        return NULL;
    }

    line[len] = '\0';  // Null-terminate the string
    return line;
}

// Function to implement heredoc (reads until delimiter is matched)
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
        restore_control_echo();
        restore_signal_handling(); // Restore signal handling for parent

        // Handle child process exit status
        if (WIFSIGNALED(status))
        {
            write(STDOUT_FILENO, "\n", 1);
            close(fds[0]);
            return -1;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
        {
            write(STDOUT_FILENO, "\n", 1);  // heredoc exited via SIGINT
            close(fds[0]);
            return -1;
        }

        close(fds[0]);
        return -1;
    }
}

int main(void)
{
    setup_signals();
    suppress_control_echo();

    while (1)
    {
        if (signal_received)
        {
            write(STDOUT_FILENO, "\nShell: SIGINT received\n", 24);
            signal_received = 0;  // Reset signal_received flag after handling
        }

        write(STDOUT_FILENO, "graceoutershell: ", 17);

        char *input = mini_getline();
        if (!input)
        {
            // If input is NULL, check if it was due to signal interruption
            if (signal_received)
            {
                // Reset signal_received flag, continue the loop and prompt again
                signal_received = 0;
                continue;
            }
            
            // If not interrupted by signal, break out of the loop and exit the shell
            write(STDOUT_FILENO, "Main loop: Input was NULL, exiting shell\n", 41);
            break;
        }

        // Process input (for now, just a simple check)
        if (ft_strcmp(input, "heredoc") == 0)
        {
            write(STDOUT_FILENO, "Main: Calling ft_heredoc\n", 26);
            int fd = ft_heredoc("EOF");
            if (fd == -1)
            {
                write(STDOUT_FILENO, "Main: Heredoc failed\n", 21);
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

    write(STDOUT_FILENO, "Main: Reached end of program, exiting\n", 38);
    return 0;
}