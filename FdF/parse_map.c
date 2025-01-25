/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 07:53:14 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h> //NEED TO REPLACE WITH OWN
#include <string.h>
#include <unistd.h>

// READ THE WHOLE FILE INTO A STRING(BUFFER)
// DETERMINE WIDTH AND HEIGHT
// LOOK FOR NEW LINE  = rows
// LOOK FOR WIDTH COUNT WORDS and check they are the same otherwise throw error
// record rows of any non empty lines until EOF ie GNL=0

// NESTED LOOP
// FILL WIDTH
// FILL HEIGHT
////store MIN MAX
// char	*read_file_to_buffer(const char *filename)
// {
// 	int		fd;
// 	char	*buffer;
// 	int		total_bytes_read;
// 	int		bytes_read;
// 	char	*new_buffer;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		handle_error("Failed to open file");
// 	buffer = malloc(BUFFSIZE + 1);
// 	if (!buffer)
// 	{
// 		close(fd);
// 		handle_error("Memory allocation error");
// 	}
// 	total_bytes_read = 0;
// 	while ((bytes_read = read(fd, buffer + total_bytes_read, BUFFSIZE)) > 0)
// 	{
// 		total_bytes_read += bytes_read;
// 		if (total_bytes_read + BUFFSIZE > total_bytes_read)
// 		{
// 			new_buffer = malloc(total_bytes_read + BUFFSIZE + 1);
// 			if (!new_buffer)
// 			{
// 				free(buffer);
// 				close(fd);
// 				handle_error("Memory allocation error");
// 			}
// 			memcpy(new_buffer, buffer, total_bytes_read);
// 			free(buffer);
// 			buffer = new_buffer;
// 		}
// 	}
// 	if (bytes_read == -1)
// 	{
// 		free(buffer);
// 		close(fd);
// 		handle_error("Error reading file");
// 	}
// 	buffer[total_bytes_read] = '\0';
// 	close(fd);
// 	return (buffer);
// }
// TOO MANY LINES

static int	count_words(const char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ' && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*line == ' ')
		{
			in_word = 0;
		}
		line++;
	}
	return (count);
}

void	determine_dimensions(const char *buffer, t_map *map)
{
	int			cols;
	int			first_line;
	const char	*line_start = buffer;
	int			current_width;
	int			rows;

	rows = 0;
	cols = 0;
	first_line = 1;
	while (*buffer)
	{
		while (*buffer && *buffer != '\n')
			buffer++;
		if (buffer > line_start)
		{
			current_width = count_words(line_start);
			if (first_line)
			{
				cols = current_width;
				first_line = 0;
			}
			else if (current_width != cols)
				handle_error("Error: inconsistent cols in map data");
		}
		if (*buffer == '\n')
		{
			buffer++;
			rows++;
		}
	}
	map->rows = rows;
	map->cols = cols;
}

// TOO MANY LINES
// Skip any leading whitespace
// Check for end of buffer
// Move the pointer to the end of the number

static char	*skip_whitespace(char *buffer)
{
	while (*buffer == ' ' || *buffer == '\n')
		buffer++;
	return (buffer);
}

static char	*parse_number(char *buffer, long *value)
{
	*value = atol(buffer);
	while (*buffer != ' ' && *buffer != '\n' && *buffer != '\0')
		buffer++;
	return (buffer);
}

long	*read_map_into_array(t_map *map, char *buffer)
{
	int		array_size;
	long	*map_array;
	char	*tmp_buff;
	int		i;

	array_size = map->rows * map->cols;
	map_array = malloc(array_size * sizeof(long));
	if (!map_array)
	{
		fprintf(stderr, "Memory allocation failed for map_array.\n");
		exit(EXIT_FAILURE);
	}
	tmp_buff = buffer;
	i = 0;
	while (i < array_size)
	{
		tmp_buff = skip_whitespace(tmp_buff);
		if (*tmp_buff == '\0')
			break ;
		tmp_buff = parse_number(tmp_buff, &map_array[i]);
		i++;
	}
	if (i < array_size)
		fprintf(stderr, "Expected %d elems, but only %d .\n", array_size, i);
	return (map_array);
}

// long	*read_map_into_array(t_map *map, char *buffer)
// {
// 	int		array_size;
// 	long	*map_array;
// 	int		i;
// 	char	*tmp_buff;

// 	array_size = map->rows * map->cols;
// 	map_array = malloc(array_size * sizeof(long));
// 	i = 0;
// 	tmp_buff = buffer;
// 	while (i < array_size)
// 	{
// 		while (*tmp_buff == ' ' || *tmp_buff == '\n')
// 			tmp_buff++;
// 		if (*tmp_buff == '\0')
// 		{
// 			break ;
// 		}
// 		map_array[i] = atol(tmp_buff);
// 		while (*tmp_buff != ' ' && *tmp_buff != '\n' && *tmp_buff != '\0')
// 			tmp_buff++;
// 		i++;
// 	}
// 	if (i < array_size)
// 		fprintf(stderr, "Expected %d eles, %d found.\n", array_size, i);
// 	return (map_array);
// }
