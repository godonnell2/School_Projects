/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:59:05 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/28 10:27:57 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

char *get_next_line(int fd)
{
	static t_store store = {0};
	int i;

	i = 0;
	if (fd < 0)
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
		store.capacity = BUFFER_SIZE;
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
for newline imagine if there was just one newline
0-0 = 0 how do we leave space for the newline ??

read returns data beyond our newline! but we still need to 
be able to return that the next time!! we call our function
we SHOULD only ever return up untul first newline but there 
coudl be multiple!!! and we need someway to keep track of this
data in buffer
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