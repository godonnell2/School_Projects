/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 20:54:48 by gro-donn         ###   ########.fr       */
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

static t_map_point	*allocate_map_array(int size)
{
	t_map_point	*map_array;

	map_array = malloc(size * sizeof(t_map_point));
	if (!map_array)
		handle_error("Memory allocation failed for map_array.\n");
	return (map_array);
}

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

t_map_point	*read_map_into_array(t_map *map, char *buffer, int default_colour)
{
	int			array_size;
	t_map_point	*map_array;
	const char	*tmp_buff = buffer;
	int			i;

	array_size = map->rows * map->cols;
	map_array = allocate_map_array(array_size);
	i = 0;
	while (i < array_size)
	{
		tmp_buff = parse_map_point(tmp_buff, &map_array[i], default_colour);
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

// TOO MANY LINES
// Skip any leading whitespace
// Check for end of buffer
// Move the pointer to the end of the number