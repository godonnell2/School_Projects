/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/22 09:10:56 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

/*
ok so we need four functions
main one to call everything and do protections
READ ,
	from read to my buffer in a loop buffer could be small after each time you 've
read you check to find if you find a newline. if you dont find you continue so
they you call the read function again
when you do find the newline copy the line from your tmp into a new string strdup eg
move everything after your newline into the beginning of the tmp (moving it back)
and then you can return the dup string


main loop:
could have newline in buffer  and more charachters

strchr (buffer, '\n') 
	before is line we need to return and remove data from buffer using memmove
	
could not have newline in buffer just plain characters 
if(!strchr(buffer, '\n'))
	we need to read more data into buffer, append new data from read into buffer
	if EOF ( read return = 0)
		return what's in the buffer
		free buffer. 
	else 
		continue from main loop;
no buffer not initialised
	if(!buffer) 
		malloc a buffer
		continue from main loop; 
and already reached EOF 
	two iterations first no buffer not initialised
	second no newline identified

*/

char *get_next_line(int fd)
{
	static char *buffer = NULL;
	size_t bytes_read;
	char *newline_pos;
	char *line;
	char * tmp_store;
	
	if(buffer == NULL)
	{
		buffer = ft_calloc(1024,1);
		if(!buffer)
		{
			return NULL;
		}
	
	}
	
	while(1)
	{
		
		newline_pos = strchr(buffer,'\n');
		//printf("1sthit buffer: %s newline_pos: \n", buffer, newline_pos);
		if(newline_pos)
			{
			size_t line_length = newline_pos - buffer + 1;
			line = malloc(line_length +1);
			if(!line)
				{
				free(buffer);
				return NULL;
				}
			ft_strlcpy(line, buffer, line_length);
			//printf("2st copy line%s\n", line);
			line[line_length] = '\0';
			ft_memmove(buffer, newline_pos + 1, strlen(newline_pos + 1) + 1);
            return line;
			}
		else
		{
		size_t current_len = ft_strlen(buffer);
        bytes_read = read(fd, buffer + current_len, BUFFER_SIZE);
        if (bytes_read < 0)
        	{
            free(buffer);
            return NULL;
        	}

        if (bytes_read == 0)
        {
            if (current_len > 0)
            {
                line = ft_strdup(buffer);
                free(buffer);
                buffer = NULL;
                return line;
            }
            free(buffer);
            buffer = NULL;
            return NULL;
        }

        buffer[current_len + bytes_read] = '\0';
		}
    }
    return NULL;
}
/*
char	*g_test_str = "\ntest\ngrace this is a second try\n";

int		g_init = 1;
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			line_length;
	size_t		buffer_length;
	size_t		remaining_length;
	size_t		bytes_read;
	int			i;

	if (g_init)
	{
		g_init = 0;
		buffer = strdup(g_test_str);
	} // Static buffer for testing
	printf("get_next_line, buffer: '%s'\n", buffer);
	i = 0;
	line = NULL;
	if (buffer == NULL || buffer[0] == '\0')
	{
		return (NULL);
	}
	// we have a buffer size let's say it's one then we cant go down to the bottom instead
	// we need to call read
	
	while (1)
	{
		
			if (buffer[i] == '\n')
			{
				line_length = i + 2;
				line = malloc(line_length);
				if (!line)
				{
					return (NULL);
				}
				ft_strlcpy(line, buffer, line_length);
				line[line_length - 1] = '\0';
				buffer_length = ft_strlen(buffer);
				remaining_length = buffer_length - (i);
				printf("Memmove %d, remaining: %ld\n", i, remaining_length);
				ft_memmove(buffer, buffer + i + 1, remaining_length);
				// buffer[remaining_length] = '\0';
				if (remaining_length == 0)
				{
					buffer = NULL;
					return (NULL);
				}
				return (line);
			}
			i++;
		
		
			// hANDLE CASE WHERE NO NEW LINE
			if (buffer[i] != '\0')
			{
				line = malloc(ft_strlen(buffer) + 1);
				if (!line)
				{
					return (NULL);
				}
				ft_strlcpy(line, buffer, ft_strlen(buffer) + 1);
				buffer[0] = '\0';
				i = 0;
				return (line);
			}
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if(bytes_read > 0)
			{
				printf("bytes_read:%zu, buffer: %s, remaining_length:%zu", bytes_read, buffer, remaining_length);
				ft_memmove(buffer, buffer + i + 1, remaining_length);
			}
		}
	
	return (NULL); // No more lines to read
}
*/
#include <fcntl.h>
#include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	int		max;

// 	 size_t		fd;
// 	max = 25;
// 	 fd = open("test.txt", O_RDWR);
	 
// 	 while (--max) {
// 		char buff[5] = {0};
// 		size_t res = read(fd, buff, 5);
// 		printf("res= %zu, buff: %c%c%c%c%c\n", res, buff[0],buff[1],buff[2],buff[3],buff[4]);
// 	 }



// return 0;
int main(void)
{
	char	*line;
	size_t fd = open("test.txt", O_RDONLY);
	int		max = 25;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("get line returned null\n");
			break ;
		}
		if (!--max)
		{
			printf("max value reached\n");
			break ;
		}
		printf("RESULT RETURNED:'%s'\n", line);
		free(line);
	}
	return (0);
}
// int main(void)
// {
//     while (1)
// 	{
//         char* res = get_next_line(1);
//         if (!res)
// 		{
//             printf("res null\n");
//             break ;
//         }
//         printf("line: '%s'\n", res);
//         free(res);
//     return (0);
// }
// }
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("l:%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
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
The read function will fill the tmp with the character read.
*/
// NEED A STORE VAR ?? needs to hold a char* of indeterminate size
//(void) fd;
// printf("You entered: %s\n", existing_content);
// ssize_t read(int, void *, size_t)
// NEED TO PUT READ IN THE LOOOP CONDITOON!!!!
// printf("bytes_read:%zu,", bytes_read);