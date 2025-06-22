/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/30 10:11:54 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h> //NEED TO REPLACE WITH OWN
#include <string.h>
#include <unistd.h>

// instead of a long use another struct that contains the long and a colour
// and to this function you pass a default colour,
// if it does not have a comma colour

static const char	*parse_map_point(const char *buffer, t_map_point *point,
		int default_colour)
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
	return (buffer);
}

t_map_point	*read_z_color(int array_size, char *buffer, int default_colour)
{
	t_map_point	*values_z_color;
	const char	*tmp_buff = buffer;
	int			i;

	values_z_color = malloc(array_size * sizeof(t_map_point));
	if (!values_z_color)
		handle_error("Memory allocation failed for values_z_color.\n");
	i = 0;
	while (i < array_size)
	{
		tmp_buff = parse_map_point(tmp_buff, &values_z_color[i],
				default_colour);
		i++;
	}
	if (i < array_size)
	{
		free(values_z_color);
		handle_error("Incorrect number of elements.\n");
	}
	return (values_z_color);
}

static int	validate_line(const char *line_start, int *cols, int first_row)
{
	int	current_width;

	current_width = count_words(line_start);
	if (first_row)
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
	int			first_row;
	const char	*line_start = buffer;

	rows = 0;
	cols = 0;
	first_row = 1;
	while (*buffer)
	{
		buffer = find_next_line(buffer);
		if (buffer > line_start)
		{
			validate_line(line_start, &cols, first_row);
			first_row = 0;
		}
		rows++;
	}
	map->rows = rows;
	map->cols = cols;
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

// TOO MANY LINES
// Skip any leading whitespace
// Check for end of buffer
// Move the pointer to the end of the number