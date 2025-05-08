#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <termios.h>

int signal_received = 0;

void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    signal_received = 1;  // Set flag to handle in the main shell
}

void sigquit_handler(int sig)
{
    (void)sig;
    // Do nothing during heredoc to suppress "Quit: 3"
}

void setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void handle_signal_in_heredoc(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // During heredoc, we ignore SIGQUIT and set SIGINT to default behavior
    sa_int.sa_handler = SIG_DFL;  // Default SIGINT behavior
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;  // Ignore SIGQUIT (Ctrl+\)
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void restore_signal_handling(void)
{
    // Restore SIGINT to default behavior after heredoc
    struct sigaction sa_int;
    sa_int.sa_handler = SIG_DFL;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Restore SIGQUIT to default behavior
    struct sigaction sa_quit;
    sa_quit.sa_handler = SIG_DFL;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int mini_getline(char **line)
{
    size_t len = 0;
    ssize_t r;
    char *buffer = malloc(100);  // Temporary buffer to read input

    if (!buffer)
        return -1;

    while ((r = read(STDIN_FILENO, buffer + len, 1)) > 0)
    {
        if (buffer[len] == '\n')
            break;
        len++;
    }

    if (r == -1 && errno == EINTR)  // Interrupted by signal
    {
        free(buffer);
        return -1;
    }

    if (r == 0 && len == 0)  // End of file or no input
    {
        free(buffer);
        return 0;
    }

    buffer[len] = '\0';
    *line = buffer;
    return 1;
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

        char *line;
        while (1)
        {
            write(STDOUT_FILENO, "> ", 2);
            if (mini_getline(&line) <= 0)
                break;

            if (strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }

            write(fds[1], line, strlen(line));
            write(fds[1], "\n", 1);
            free(line);
        }

        close(fds[1]);
        exit(0);
    }
    else
    {
        // Parent process
        close(fds[1]);
        int status;
        waitpid(pid, &status, 0); // Wait for child to exit
        restore_signal_handling(); // Restore signal handling after heredoc

        if (WIFSIGNALED(status))  // Child exited due to signal (e.g., Ctrl+C)
        {
            write(STDOUT_FILENO, "\n", 1);
            close(fds[0]);
            return -1;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)  // Child exited via SIGINT
        {
            write(STDOUT_FILENO, "\n", 1);
            close(fds[0]);
            return -1;
        }

        close(fds[0]);
        return 0;
    }
}

int main(void)
{
    setup_signals();

    while (1)
    {
        char *input = NULL;
        write(STDOUT_FILENO, "graceoutershell: ", 17);
        if (mini_getline(&input) <= 0)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }

        if (strcmp(input, "heredoc") == 0)
        {
            write(STDOUT_FILENO, "Main: Calling ft_heredoc\n", 26);
            int fd = ft_heredoc("EOF");
            if (fd == -1)
            {
                write(STDOUT_FILENO, "Main: Heredoc failed\n", 22);
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