/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:07:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/24 18:38:58 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //NEED TO REPLACE WITH OWN

void	find_min_max(long *array, int array_size, t_map *map)
{
	int	i;

	if (array_size <= 0)
	{
		map->z_min = 0;
		map->z_max = 0;
		return ;
	}
	map->z_min = array[0];
	map->z_max = array[0];
	i = 1;
	while (i < array_size)
	{
		if (array[i] < map->z_min)
		{
			map->z_min = array[i];
		}
		if (array[i] > map->z_max)
		{
			map->z_max = array[i];
		}
		i++;
	}
}

void	generate_3d_points(t_map *map, long *map_array, t_point3d *points)
{
	int	index;
	int	y;
	int	x;

	index = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			points[index].x = x;
			points[index].y = y;
			points[index].z = map_array[y * map->cols + x];
			index++;
			x++;
		}
		y++;
	}
}

// so basically this is how we drop the z axis
// because screens dont have a z axis
// Retrieve the 3D coordinates from the points array
// Apply the isometric projection formula
// 0.523599 radians = 30 degrees
// Store the resulting 2D point in the iso_points array

void	convert_to_isometric(t_map *map, t_point3d *points,
		t_point2d *iso_points)
{
	float	iso_x;
	float	iso_y;
	int		i;

	i = 0;
	while (i < map->rows * map->cols)
	{
		iso_x = (points[i].x - points[i].y) * cos(0.523599);
		iso_y = (points[i].x + points[i].y) * sin(0.523599) - points[i].z;
		iso_points[i].x = iso_x;
		iso_points[i].y = iso_y;
		i++;
	}
}

// Center horizontally
// Center vertically
void	scale_and_offset_points(t_point2d *iso_points, t_map *map,
		int window_width, int window_height)
{
	int	total_points;
	int	offset_x;
	int	offset_y;
	int	i;

	total_points = map->cols * map->rows;
	offset_x = window_width / 2;
	offset_y = window_height / 2;
	i = 0;
	while (i < total_points)
	{
		iso_points[i].x *= SCALE_FACTOR;
		iso_points[i].y *= SCALE_FACTOR;
		iso_points[i].x += offset_x;
		iso_points[i].y += offset_y;
		i++;
	}
}

// t_edge edges[] = {
// 	{.start = 0, .end = 1},
// 	{.start = 1, .end = 3},
// 	{.start = 3, .end = 2},
// 	{.start = 2, .end = 0},
// };

// NEED TO POPULATE SOMETHING LIKE THIS FN
// Connect to the right neighbor
// if (x < cols - 1)
// Connect to the bottom neighbor
// if (y < rows - 1)
void	populate_edges(t_map *map, t_edge **edges, int *edges_count)
{
	int	total_edges;
	int	current_index;

	total_edges = (map->cols - 1) * map->rows + (map->rows - 1) * map->cols;
	*edges = malloc(total_edges * sizeof(t_edge));
	if (edges == NULL)
	{
		fprintf(stderr, "Memory allocation failed for edges.\n");
		exit(EXIT_FAILURE);
	}
	*edges_count = 0;
	for (int y = 0; y < map->rows; y++)
	{
		for (int x = 0; x < map->cols; x++)
		{
			current_index = y * map->cols + x;
			if (x < map->cols - 1)
			{
				(*edges)[*edges_count].start = current_index;
				(*edges)[*edges_count].end = current_index + 1;
				(*edges_count)++;
			}
			if (y < map->rows - 1)
			{
				(*edges)[*edges_count].start = current_index;
				(*edges)[*edges_count].end = current_index + map->cols;
				(*edges_count)++;
			}
		}
	}
}

// read ints and skip newlines and spaces until EOF or all
//  (then check how many elements you were expecting)
// Convert 3d pts to 2dpts
// find the edges and the vertices
// find min and max FINISHED like the square printing
// calc x,y so that i have 3d pts(x, y,z )
// calculate the edges only dependent on the cols and the rows
// the edges are just teh grid
// scale min max

// The grid edges will form the structure, and the z values will create the
//  "rows" variations that make the grid look like a 3D terrain in
//  isometric projection.