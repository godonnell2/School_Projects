/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/20 21:13:28 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

/*
ok so we need four functions
main one to call everything and do protections
READ , from read to my buffer in a loop buffer could be small after each time you 've
read you check to find if you find a newline. if you dont find you continue so
they you call the read function again
when you do find the newline copy the line from your tmp into a new string strdup eg
move everything after your newline into the beginning of the tmp (moving it back)
and then you can return the dup string


*/

char* g_test_str = "grace";
int g_init = 1;
char *get_next_line(int fd) {
    static char *buffer;
	
	if (g_init) {
		g_init = 0;
		buffer = strdup(g_test_str);
	}  // Static buffer for testing

	printf("get_next_line, buffer: '%s'\n", buffer);
     int i = 0; // Current index in the buffer
    char *line = NULL;

    // If buffer is empty, return NULL
    if (buffer == NULL || buffer[0] == '\0') 
	{
        return NULL;
    }

   
    // while (buffer[i])
    while (1) 
	{
        if (buffer[i] == '\n' || buffer[i] == '\0') {
           
            int line_length = i + 2; 
            line = malloc(line_length);
            if (!line) 
			{
                return NULL; 
            }

            ft_strlcpy(line, buffer, line_length);
			line[line_length-1] = '\0';
          
            size_t buffer_length = ft_strlen(buffer);
            size_t remaining_length = buffer_length - (i);
            printf("Memmove %d, remaining: %ld\n", i, remaining_length);
			ft_memmove(buffer, buffer + i + 1, remaining_length);
            //buffer[remaining_length] = '\0'; 
			if(remaining_length == 0)
				{
					buffer = NULL;
					return NULL;
				}
            return line;
        }
        i++;

  //hANDLE CASE WHERE NO NEW LINE 
		  if (buffer[0] != '\0')
		  {
			line = malloc(ft_strlen(buffer) + 1);
			if (!line) 
				{
            	return NULL; 
		  		}
			 ft_strlcpy(line, buffer, ft_strlen(buffer) + 1);
			
			buffer[0] = '\0';
        	i = 0;

        return line;
    }
	return NULL;
    }


   
	

    return NULL; // No more lines to read
}

/


#include <stdio.h>
int main(void) {
    /
    char *line;
	int max = 5;
    while (1) { 
        line = get_next_line(0);
		if (line == NULL) {
			printf("get line returned null\n");
			break;
		}
		if (!--max) {
			printf("max value reached\n");
			break;
		}
		printf("'%s'\n", line);
        free(line);
    }
    return 0;
}
// int main(void) 
// {
//     while (1) 
// 	{
//         char* res = get_next_line(1);
//         if (!res) 
// 		{
//             printf("res null\n");
//             break;
//         }
//         printf("line: '%s'\n", res);
//         free(res);
//     return 0;
// }
// }
/*
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file");
		return 1;
	}

	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{

		printf("l:%s\n", line);
		free(line);
	}

	close(fd);
	return 0;
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