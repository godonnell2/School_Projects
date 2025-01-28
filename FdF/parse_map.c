/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 19:12:19 by gro-donn         ###   ########.fr       */
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

// instead of a long use another struct that contains the long and a colour
// and to this function you pass a default colour,
	//if it does not have a comma colour


static t_map_point *allocate_map_array(int size)
{
    t_map_point *map_array = malloc(size * sizeof(t_map_point));
    if (!map_array)
        handle_error("Memory allocation failed for map_array.\n");
    return map_array;
}

static const char *parse_map_point(const char *buffer, t_map_point *point, int default_colour)
{
    buffer = skip_whitespace(buffer);
    if (*buffer == '\0')
        handle_error("Unexpected end of input.\n");
    buffer = parse_number(buffer, &point->z);
    if (*buffer == ',')
    {
        buffer++;
        buffer = parse_hex_color(buffer, &point->color);
    }
    else
    {
        point->color = default_colour;
    }
    return buffer;
}

t_map_point *read_map_into_array(t_map *map, char *buffer, int default_colour)
{
    int array_size = map->rows * map->cols;
    t_map_point *map_array = allocate_map_array(array_size);
    const char *tmp_buff = buffer;
    int i = 0;

    while (i < array_size)
    {
        tmp_buff = parse_map_point(tmp_buff, &map_array[i], default_colour);
        i++;
    }
    if (i < array_size)
        handle_error("Incorrect number of elements.\n");
    return map_array;
}
// t_map_point	*read_map_into_array(t_map *map, char *buffer, int default_colour)
// {
// 	int			array_size;
// 	t_map_point	*map_array;
// 	const char	*tmp_buff;
// 	int			i;

// 	array_size = map->rows * map->cols;
// 	map_array = malloc(array_size * sizeof(t_map_point));
// 	if (!map_array)
// 		handle_error("Memory allocation failed for map_array.\n");
// 	tmp_buff = buffer;
// 	i = 0;
// 	while (i < array_size)
// 	{
// 		tmp_buff = skip_whitespace(tmp_buff);
// 		if (*tmp_buff == '\0')
// 			break ;
// 		tmp_buff = parse_number(tmp_buff, &map_array[i].z);
// 		if (*tmp_buff == ',')
// 		{
// 			tmp_buff++;
// 			tmp_buff = parse_hex_color(tmp_buff, &map_array[i].color);
// 		}
// 		else
// 			map_array[i].color = default_colour;
// 		i++;
// 	}
// 	if (i < array_size)
// 		handle_error("Incorrect number of elements.\n");
// 	return (map_array);
// }

// READ THE WHOLE FILE INTO A STRING(BUFFER)
// DETERMINE WIDTH AND HEIGHT
// LOOK FOR NEW LINE  = rows
// LOOK FOR WIDTH COUNT WORDS and check they are the same otherwise throw error
// record rows of any non empty lines until EOF ie GNL=0

// NESTED LOOP
// FILL WIDTH
// FILL HEIGHT
////store MIN MAX


// TOO MANY LINES
// Skip any leading whitespace
// Check for end of buffer
// Move the pointer to the end of the number