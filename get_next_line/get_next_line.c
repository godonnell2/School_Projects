/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/23 14:50:57 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

static void	*grow_store(char **store, size_t *store_size)
{
	char	*new_ptr;
	char	*ptr;
	size_t	i;
	size_t	size_to_copy;

	size_to_copy = *store_size;
	ptr = *store;
	*store_size *= 2;
	new_ptr = ft_calloc(*store_size, 1);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < size_to_copy)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

static char	*get_stored_line(char **store, char *newline_pos)
{
	size_t	line_length;
	char	*line;
	size_t	i;

	i = 0;
	line_length = newline_pos - (*store) + 1;
	line = malloc(line_length + 1);
	if (line == NULL)
		return (free_store(store));
	ft_strlcpy(line, *store, line_length + 1);
	newline_pos++;
	while (newline_pos[i])
	{
		(*store)[i] = newline_pos[i];
		i++;
	}
	(*store)[i] = '\0';
	return (line);
}

char	*handle_finalread(size_t bytes_read, size_t current_len, char **store)
{
	char	*line;

	if (bytes_read == 0 && current_len > 0)
	{
		line = malloc(current_len + 1);
		if (!line)
			return (free_store(store));
		ft_strlcpy(line, *store, current_len + 1);
	}
	else
		line = NULL;
	free_store(store);
	return (line);
}

char	*get_next_line_store(int fd, char **store, size_t *store_size)
{
	size_t	bytes_read;
	char	*newline_pos;
	size_t	current_len;

	while (1)
	{
		newline_pos = strchr(*store, '\n');
		if (newline_pos)
			return (get_stored_line(store, newline_pos));
		else
		{
			current_len = ft_strlen(*store);
			if (current_len + BUFFER_SIZE >= *store_size)
			{
				*store = grow_store(store, store_size);
				if (!(*store))
					return (NULL);
			}
			bytes_read = read(fd, (*store) + current_len, BUFFER_SIZE);
			if (bytes_read < 1)
				return (handle_finalread(bytes_read, current_len, store));
			(*store)[current_len + bytes_read] = '\0';
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*store = NULL;
	static size_t	store_size = 0;

	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (store != NULL)
			free_store(&store);
		return (NULL);
	}
	if (store == NULL)
	{
		store = ft_calloc(BUFFER_SIZE, 1);
		if (!store)
			return (NULL);
		store_size = BUFFER_SIZE;
	}
	return (get_next_line_store(fd, &store, &store_size));
}

/*
ok so we need four functions
main one to call everything and do protections
READ ,
from read to my store in a loop store could be small after each time you 've
read you check to find if you find a newline. if you dont find you continue so
they you call the read function again
when you do find the newline copy the line from your tmp into a new string
strdup eg
move everything after your newline into the beginning of the tmp
 (moving it back)
and then you can return the dup string

DIFFERENT CONDITIONS
main loop:
could have newline in store  and more charachters

strchr (store, '\n')
	before is line we need to return and remove data from store using memmove

could not have newline in store just plain characters
if(!strchr(store, '\n'))
	we need to read more data into store, append new data from read into store
	if EOF ( read return = 0)
		return what's in the store
		free store.
	else
		continue from main loop;
no store not initialised
	if(!store)
		malloc a store
		continue from main loop;
and already reached EOF
	two iterations first no store not initialised
	second no newline identified

*/

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