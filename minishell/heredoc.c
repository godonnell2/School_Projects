/*

Ctrl+C (SIGINT) should interrupt the heredoc, print a newline,
 and return to the shell prompt.

Ctrl+D should act like EOF — this is already handled by readline()
returning NULL.

The shell should not exit when SIGINT is received during heredoc input.

After heredoc ends, restore the original signal behavior.



*/
#include "minishell.h"

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define READ 0
#define WRITE 1
#define STDIN 0

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
//  &&&&make my own sig handler and adapt the normal behaviourt
// TEST MAX HERE DOC 64 KIB
// ALSO NEED TO REMEMBER TO CLOSE READ END AFTER DUP2 in next fork

int	ft_heredoc(char *endoffile)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("heredoc:pipe cretion");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if ((ft_strcmp(endoffile, line) == 0))
		{
			free(line);
			break ;
		}
		write(pipe_fd[WRITE], line, ft_strlen(line));
		write(pipe_fd[WRITE], "\n", 1);
		free(line);
	}
	close(pipe_fd[WRITE]);
	return (pipe_fd[READ]);
}

// void ft_heredoc(char * endoffile)
// {
//     int fds[2];
//     //fills it with new file descriptor numbers assigned by the kernel.
//     if (pipe(fds) == -1)
//     {
//         perror("heredoc:pipe cretion");
//         exit(EXIT_FAILURE);
//     }

//     pid_t pid = fork();
//     if (pid == -1)
//     {
//         perror("heredoc:fork");
//         exit(EXIT_FAILURE); //is coded in stdlib
//     }

//     if(pid == 0)
//     {
//         close(fds[READ]);

//         char *line;
//         while(1)
//         {
//             line = readline("> ");
//             if (!line)
//              {
//                 break ;
//             }
//             if((ft_strcmp(endoffile, line)== 0))
//             {
//                 free(line);
//                 break ;
//             }

//             write(fds[WRITE],line ,ft_strlen(line));
//             write(fds[WRITE], "\n", 1);
//             free(line);
//         }
//         close(fds[WRITE]);
//         exit(EXIT_SUCCESS);
//     }
//     else
//     //ie we're in the parent
//     {
//         close(fds[WRITE]);
//         //heredocinput becomes stdin for next cmd
//         // need to do another fork to exec the next cmd
//        if (dup2(fds[READ], STDIN_FILENO) == -1)
//         {
//             perror("heredoc:dup2");
//             exit(EXIT_FAILURE);
//         }
//         close(fds[READ]);
//         waitpid(pid, NULL, 0);

//        //so i put the wait at teh end because the command will read from
//        //the pipe while the child writes to it,
//	preventing deadlock if heredoc hits max size 64KB.
//     }
// }

int	main(void)
{
	ft_heredoc("EOF");
	return (0);
}

/*

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