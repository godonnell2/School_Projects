/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:09:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/02 11:22:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*line;
	size_t		line_length;

	line = NULL;
	line_length = 0;
	while (fd >= 0)
	{
		if (buffer[0] != '\0')
		{
			line = strjoin_consumebuff(line, buffer, &line_length);
			if (line == NULL || line[line_length - 1] == '\n')
				break ;
			continue ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	int		max;
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	fd = 0;
// 	max = 25;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!--max)
// 		{
// 			printf("Max iterations reached\n");
// 			break ;
// 		}
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		{
// 			printf("get_next_line found a NULL\n");
// 			break ;
// 		}
// 		printf("RESULT RETURNED:'%s'\n", line);
// 		free(line);
// 	}
// }

// if there is data we check to see if there's data in the store
// we look for first newline strchr DONE!!
// as long as theres data in store have to clear it
// if we find a new line DONE!!
// we append up until and including newline to line strjoin DONE!!
// we use memmove to move from beyond newline to the back of the store DONE!!
// return the line DONE
// else append all of the store to line strjoin
// else we read into the store DONE!!!