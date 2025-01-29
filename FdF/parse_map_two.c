/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:53:34 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/29 11:30:26 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
