/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/26 08:09:08 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

void	*free_store_value(t_store *store)
{
	free(store->value);
	store->value = NULL;
	store->size = 0;
	return (NULL);
}

static void	grow_store(t_store *store)
{
	char	*ptr;
	size_t	i;
	size_t	size_to_copy;

	size_to_copy = store->size;
	ptr = store->value;
	store->size *= 2;
	store->value = malloc(store->size);
	i = 0;
	if (store->value == NULL)
	{
		free(ptr);
		store->size = 0;
		return ;
	}
	while (i < store->size)
	{
		if (i < size_to_copy)
			store->value[i] = ptr[i];
		else
			store->value[i] = 0;
		i++;
	}
	free(ptr);
}

static char	*get_stored_line(t_store *store)
{
	size_t	line_length;
	char	*line;
	char	*newline_pos;
	size_t	i;

	newline_pos = store->value;
	while (*newline_pos && *newline_pos != '\n')
		newline_pos++;
	if (*newline_pos != '\n')
		return (NULL);
	line_length = newline_pos - store->value + 1;
	line = malloc(line_length + 1);
	if (!line)
		return (free_store_value(store));
	i = 0;
	while (i < line_length)
	{
		line[i] = store->value[i];
		i++;
	}
	line[i] = '\0';
	i = 0;
	while (newline_pos[i + 1])
	{
		store->value[i] = newline_pos[i + 1];
		i++;
	}
	store->value[i] = '\0';
	return (line);
}

static char	*handle_finalread(size_t bytes_read, size_t current_len,
		t_store *store)
{
	char	*line;
	size_t	i;

	i = 0;
	if (bytes_read == 0 && current_len > 0)
	{
		line = malloc(current_len + 1);
		if (!line)
			return (free_store_value(store));
		while (i < current_len && store->value[i])
		{
			line[i] = store->value[i];
			i++;
		}
		line[i] = '\0';
	}
	else
		line = NULL;
	free_store_value(store);
	return (line);
}

static char	*get_next_line_store(int fd, t_store *store)
{
	size_t	bytes_read;
	size_t	current_len;
	char	*tmp_str;

	while (1)
	{
		tmp_str = get_stored_line(store);
		if (tmp_str || store->value == NULL)
			return (tmp_str);
		tmp_str = store->value;
		while (*tmp_str)
			tmp_str++;
		current_len = tmp_str - store->value;
		if (current_len + BUFFER_SIZE >= store->size)
		{
			grow_store(store);
			if (store->value == NULL)
				return (NULL);
		}
		bytes_read = read(fd, store->value + current_len, BUFFER_SIZE);
		if (bytes_read < 1)
			return (handle_finalread(bytes_read, current_len, store));
		store->value[current_len + bytes_read] = '\0';
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_store	store = {0};
	int				i;

	i = 0;
	if (fd < 0 || (read(fd, 0, 0) < 0))
	{
		if (store.value != NULL)
			free_store_value(&store);
		return (NULL);
	}
	if (store.value == NULL)
	{
		store.value = malloc(BUFFER_SIZE);
		if (!store.value)
			return (NULL);
		store.size = BUFFER_SIZE;
		while (i < BUFFER_SIZE)
		{
			store.value[i] = 0;
			i++;
		}
	}
	return (get_next_line_store(fd, &store));
}

/*
int	main(void)
{
	char	*line;
	size_t	fd;
	int		max;

	fd = open("test.txt", O_RDONLY);
	max = 25;
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
*/

/*
Hello, World!

This is a test file.
It contains multiple lines.
Each line will be read one by one.
End of file without newline
*/

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