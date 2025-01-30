/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:07:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/30 21:59:38 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	find_min_max(t_map *map)
{
	int			i;
	int			array_size;
	t_map_point	*values;

	values = map->values_z_color;
	array_size = map->cols * map->rows;
	map->z_min = map->values_z_color[0].z;
	map->z_max = map->values_z_color[0].z;
	i = 1;
	while (i < array_size)
	{
		if (values[i].z < map->z_min)
		{
			map->z_min = values[i].z;
		}
		if (values[i].z > map->z_max)
		{
			map->z_max = values[i].z;
		}
		i++;
	}
}

// so basically this is how we drop the z axis
// because screens dont have a z axis
// Retrieve the 3D coordinates from the points array
// Apply the isometric projection formula
// 0.523599 radians = 30 degrees
// Store the resulting 2D point in the iso_points array
// x is indepent of the z interesting interseting
// 30° rotation.
// need to invert y coordinate   iso_y = window_height - iso_y; he origin (0,
//		0) is the upper left corner of the window,
//  the x and y axis respectivelyInversion of Y-Axis:
// etric projection of a 3D point  (x,y,z)
// onto a 2D plane involves a rotation of the point in 3D space.
//  Since the y-axis in MLX points down,
//	you may need to invert the y-coordinate after
//  calculating the isometric y-coordinate.
//  The formula you're using is a simplified version of this transformation:

// iso_x = (x - y) * cos(θ)
// iso_y = (x + y) * sin(θ) - z

void	to_pixel_coords(const t_map *map, const t_point3d *points,
		t_point2d *iso_points, t_point2d window_size)
{
	float		iso_x;
	float		iso_y;
	float		scale_factor;
	t_point2d	offset;
	int			i;

	scale_factor = fmin(window_size.x / 1.6f, window_size.y / 1.6f);
	offset.x = window_size.x / 2;
	offset.y = window_size.y / 4;
	i = 0;
	while (i < map->rows * map->cols)
	{
		iso_x = (points[i].x - points[i].y) * cos(0.523599);
		iso_y = (points[i].x + points[i].y) * sin(0.523599) - (points[i].z
				/ 10);
		iso_points[i].x = iso_x * scale_factor + offset.x;
		iso_points[i].y = iso_y * scale_factor + offset.y;
		i++;
	}
}
// Center horizontally
// Center vertically

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
// void	populate_edges(t_map *map, t_edge **edges, int *edges_count)

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