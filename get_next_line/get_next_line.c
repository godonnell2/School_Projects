/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/15 12:24:13 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{	
	char *store = malloc(1000);
	//need to add NULL check
	size_t bytes_read;
	char *buffer;
	
	int keep_reading = 1;
	// NEED A STORE VAR ?? needs to hold a char* of indeterminate size
	buffer = malloc(BUFFER_SIZE + 1);
	//  if (!buffer)
    //     return NULL; 

	// if (fd <0 || buffer <= 0) 
    // {
    //     free(buffer); 
    //     return NULL; 
    // }
	
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	//NEED TO PUT READ IN THE LOOOP CONDITOON!!!!
	printf("bytes_read:%zu,", bytes_read);
	int i = 0;
	while(keep_reading && bytes_read > 0)
	{
		
		store[i] =	buffer[i];
		i++;
		if (buffer[i] == '\n')
			{
			keep_reading = 0;
			}
		bytes_read--;
		store[i]= '\0';
	}
	//(void) fd;
	printf("You entered: %s\n", store);
	return store;

}
//ssize_t read(int, void *, size_t)

int main()
{
	const char *temp_file = "test.txt";
	int fd;
	fd = open(temp_file, O_RDWR | O_CREAT);
	
	printf("%s", get_next_line(fd));
	
	//char *line = get_next_line(0);
	//  if (line)
	// printf("You entered: %s\n", line); 
    //     free(line);
	
	return 0;
}



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
