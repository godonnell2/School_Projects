/*
>> should redirect output in append mode.
open is a sys call!!
ou're learning how to control I/O at the kernel level —
 this is where real shell-building power lives.
 0644 = owener read write everyone else read only
*/
#include "minishell.h"
#include <fcntl.h> // For O_* flags
#include <sys/wait.h>
#include <unistd.h> // For open(), write(), close()

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

int	ft_append(char *arg, char *filename)
{
	int	fd;
	int	pid;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		write(fd, arg, ft_strlen(arg));
		write(fd, "\n", 1);
		close(fd);
		return exit_code = 0;
	}
	else
	{
		wait(NULL);
		return exit_code= 1; 
	}
}

// int	main(void)
// {
// 	ft_append("this is a test", "file.txt");
// }
