/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:07:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/31 10:22:14 by gro-donn         ###   ########.fr       */
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

// typedef struct s_edge
// {
// 	int start;
// 	int end;
// } t_edge;
// need -1 for out of bounds access it can only have neighbour
// if it is not the last one
// if the index does not correspond to the last col create an edge
// from index to index +1
// and then if index does not correspond to the last row create an edge
// index to index + cols

t_edge	*populate_edges(t_map *map, int total_edges)
{
	int		i;
	int		index;
	t_edge	*edges;

	edges = malloc(total_edges * sizeof(t_edge));
	if (edges == NULL)
		return (NULL);
	i = 0;
	index = 0;
	while (index < map->cols * map->rows)
	{
		if (index % map->cols < map->cols - 1)
		{
			edges[i].start = index;
			edges[i++].end = index + 1;
		}
		if (index / map->cols < map->rows - 1)
		{
			edges[i].start = index;
			edges[i++].end = index + map->cols;
		}
		index++;
	}
	return (edges);
}

static void	populate_normalise_3d_points(t_point3d *points, const t_map *map)
{
	float		range_z;
	int			i;
	t_map_point	*values_z_color;

	values_z_color = map->values_z_color;
	range_z = map->z_max - map->z_min;
	i = 0;
	while (i < (map->rows * map->cols))
	{
		points[i].x = (float)(i % map->cols) / (map->cols - 1);
		points[i].y = (float)(i / map->cols) / (map->rows - 1);
		if (range_z == 0)
			points[i].z = 0;
		else
			points[i].z = (float)(values_z_color[i].z - map->z_min) / range_z;
		i++;
	}
}

t_point2d	*prepare_iso_points(const t_map *map, t_point2d window_size)
{
	t_point3d	*points;
	t_point2d	*iso_points;

	points = malloc(map->rows * map->cols * sizeof(t_point3d));
	if (!points)
	{
		handle_error("Memory allocation failed for points.");
		return (NULL);
	}
	iso_points = malloc(map->rows * map->cols * sizeof(t_point2d));
	if (!iso_points)
	{
		free(points);
		handle_error("Memory allocation failed for iso_points.");
		return (NULL);
	}
	populate_normalise_3d_points(points, map);
	to_pixel_coords(map, points, iso_points, window_size);
	free(points);
	return (iso_points);
}

/*

Instead of using the equation of a line (y = mx + b),
 which involves floating-point calculations, Bresenham’s algorithm only uses
 integer addition, subtraction, and bit shifts.

It works by deciding at each step whether the next pixel should move
horizontally or diagonally to stay as close to the ideal line as possible.
Start at the first point (x0, y0).
Calculate the differences:
dx = x1 - x0 (horizontal distance)
dy = y1 - y0 (vertical distance)
Determine the decision parameter D:
D = 2dy - dx (initial decision value)
Loop through each x-value from x0 to x1:
If D < 0, move horizontally (x++) and update D = D + 2dy.
If D ≥ 0, move diagonally (x++, y++) and update D = D + 2(dy - dx).
Repeat until you reach (x1, y1).endpoint
​
  are not necessarily between 0 and 1.
  They are actual pixel coordinates on the screen (e.g.,
𝑥0 = 50 𝑥1=200 etc.).

*/