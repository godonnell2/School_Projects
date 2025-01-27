/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/27 16:26:44 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h> //NEED TO REPLACE WITH OWN
#include <string.h>
#include <unistd.h>

static int	validate_line(const char *line_start, int *cols, int first_line)
{
	int	current_width;

	current_width = count_words(line_start);
	if (first_line)
	{
		*cols = current_width;
	}
	else if (current_width != *cols)
	{
		handle_error("Error: inconsistent cols in map data");
	}
	return (current_width);
}

static const char	*find_next_line(const char *buffer)
{
	while (*buffer && *buffer != '\n')
		buffer++;
	if (*buffer == '\n')
		buffer++;
	return (buffer);
}

void	determine_dimensions(const char *buffer, t_map *map)
{
	int			rows;
	int			cols;
	int			first_line;
	const char	*line_start = buffer;

	rows = 0;
	cols = 0;
	first_line = 1;
	while (*buffer)
	{
		buffer = find_next_line(buffer);
		if (buffer > line_start)
		{
			validate_line(line_start, &cols, first_line);
			first_line = 0;
		}
		rows++;
	}
	map->rows = rows;
	map->cols = cols;
}

//instead of a long use another struct that contains the long and a colour 
//and to this function you pass a default colour, if it does not have a comma colour
t_map_point	* read_map_into_array(t_map *map, char *buffer, int default_colour)
{
	int		array_size;
	t_map_point	*map_array;
	const char * tmp_buff;
	int		i;

	array_size = map->rows * map->cols;
	map_array = malloc(array_size * sizeof(t_map_point));
	if (!map_array)
	{
		 handle_error("Memory allocation failed for map_array.\n");
	}
	tmp_buff = buffer;
	i = 0;
	while (i < array_size)
	{
		tmp_buff = skip_whitespace(tmp_buff);
		if (*tmp_buff == '\0')
			break ;
		tmp_buff = parse_number(tmp_buff, &map_array[i].z);
        if (*tmp_buff == ',')
        {
            tmp_buff++;
            tmp_buff = parse_hex_color(tmp_buff, &map_array[i].color);
        }
        else
        {
            
            map_array[i].color = default_colour;
        }
		i++;
	}
	if (i < array_size)
		handle_error("Incorrect number of elements.\n");
	return (map_array);
}

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
// 		ft_printf(stderr, "Expected %d eles, %d found.\n", array_size, i);
// 	return (map_array);
// }

// void	determine_dimensions(const char *buffer, t_map *map)
// {
// 	int			cols;
// 	int			first_line;
// 	const char	*line_start = buffer;
// 	int			current_width;
// 	int			rows;

// 	rows = 0;
// 	cols = 0;
// 	first_line = 1;
// 	while (*buffer)
// 	{
// 		while (*buffer && *buffer != '\n')
// 			buffer++;
// 		if (buffer > line_start)
// 		{
// 			current_width = count_words(line_start);
// 			if (first_line)
// 			{
// 				cols = current_width;
// 				first_line = 0;
// 			}
// 			else if (current_width != cols)
// 				handle_error("Error: inconsistent cols in map data");
// 		}
// 		if (*buffer == '\n')
// 		{
// 			buffer++;
// 			rows++;
// 		}
// 	}
// 	map->rows = rows;
// 	map->cols = cols;
// }

// TOO MANY LINES
// Skip any leading whitespace
// Check for end of buffer
// Move the pointer to the end of the number