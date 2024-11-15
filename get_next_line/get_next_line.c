/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/15 17:32:39 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char	*store;
	char	*buffer;
	int		i;
	int bytes_read;

	store = malloc(1000);
	if (store == NULL)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 )
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	int j = 0;
	while ((bytes_read =read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		while(j < bytes_read)
		{
			store[i] = buffer[j];
			if (buffer[j] == '\n')
			{
				store[i] = '\0';
			}
			j++;
		}
		i++;
	}
	return (store);
}

/*
char *ft_get_the_whole_line(int fd)
{
	char * whole_text = get_next_line(fd);
	ft_strjoin();
}
*/


int	main(void)
{
	const char	*temp_file = "test.txt";
	charbuf[256];
	int			fd;
	int chars_read;

	fd = open(temp_file, O_RDWR | O_CREAT);
	while((chars_read = read(fd, buf, BUFFER_SIZE) ))
	{
		buf[chars_read] == '\0';
	printf("%s", get_next_line(fd),buf);
}
	return (0);
}

// char *line = get_next_line(0);
//  if (line)
// printf("You entered: %s\n", line);
//     free(line);

// int main ()
// {
// 	const char	*temp_filename = "test_output.txt";
// 	int			fd;
// 	char		*s;

// 	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// if (fd == -1) {
// 		perror("Failed to open file");
// 		return (1);
// 	}
// 	s = "GRACE";
// 	ft_putstr_fd(s, fd);
// 	return (0);
// }

/*
create if nonexistsent
truncate if it exists let me overwrite

check if -1 is kinda like check for null

void fd will allow you to use this fn without using this parametor
The read function will fill the buffer with the character read.
*/
// NEED A STORE VAR ?? needs to hold a char* of indeterminate size
//(void) fd;
// printf("You entered: %s\n", store);
// ssize_t read(int, void *, size_t)
// NEED TO PUT READ IN THE LOOOP CONDITOON!!!!
// printf("bytes_read:%zu,", bytes_read);