#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// if there is data we check to see if there's data in the store
// we look for first newline strchr DONE!! 
//as long as theres data in store have to clear it
// if we find a new line DONE!!
// we append up until and including newline to line strjoin DONE!!
// we use memmove to move from beyond newline to the back of the store DONE!!
// return the line DONE
// else append all of the store to line strjoin
// else we read into the store DONE!!!

char	*get_next_line(int fd)
{
	static t_store store;
	char *line = NULL;
	char *newline_pos;
    size_t line_length;
    char *cpy;
    char *temp;
    size_t remaining_bytes;

	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (store.bytes_stored > 0)
		{
            newline_pos = store.value;
             while (*newline_pos && *newline_pos != '\n')
                newline_pos++;
			if (*newline_pos == '\n') 
			{
				line_length = newline_pos - store.value + 1;
				cpy = ft_strndup(store.value, line_length);
				if (!cpy)
                {
                free(line);
					return (NULL);
                }
				temp = ft_strjoin(line, cpy);
				free(cpy);
				free(line);
				if (!temp)
					return (NULL);
				line = temp;
				remaining_bytes = store.bytes_stored - line_length;
				ft_memmove(store.value, store.value + line_length,
					remaining_bytes);
				store.bytes_stored = remaining_bytes;
				store.value[store.bytes_stored] = '\0';
				return (line);
			}
			else
			{
				char *temp = ft_strjoin(line, store.value);
				free(line);
				if (!temp)
					return (NULL);
				line = temp;
				store.bytes_stored = 0;
				store.value[0] = '\0';
			}
		}
		int bytes_read = read(fd, store.value + store.bytes_stored,
				BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0 && line)
			{
				char *temp = ft_strjoin(line, store.value);
				free(line);
				if (!temp)
					return (NULL);
				line = temp;
				store.bytes_stored = 0;
				store.value[0] = '\0';
				return (line);
			}
			free(line);
			return (NULL);
		}
		store.bytes_stored += bytes_read;
		store.value[store.bytes_stored] = '\0';
	}
}
