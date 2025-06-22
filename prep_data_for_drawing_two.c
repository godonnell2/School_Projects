/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:16:04 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/31 10:22:47 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

// t_edge	*populate_edges(t_map *map, int total_edges)
// {
// 	int		i;
// 	int		index;
// 	t_edge	*edges;

// 	edges = malloc(total_edges * sizeof(t_edge));
// 	if (edges == NULL)
// 		return (NULL);
// 	i = 0;
// 	index = 0;
// 	while (index < map->cols * map->rows)
// 	{
// 		if (index % map->cols < map->cols - 1)
// 		{
// 			edges[i].start = index;
// 			edges[i++].end = index + 1;
// 		}
// 		if (index / map->cols < map->rows - 1)
// 		{
// 			edges[i].start = index;
// 			edges[i++].end = index + map->cols;
// 		}
// 		index++;
// 	}
// 	return (edges);
// }

// static void	populate_normalise_3d_points(t_point3d *points, const t_map *map)
// {
// 	float		range_z;
// 	int			i;
// 	t_map_point	*values_z_color;

// 	values_z_color = map->values_z_color;
// 	range_z = map->z_max - map->z_min;
// 	i = 0;
// 	while (i < (map->rows * map->cols))
// 	{
// 		points[i].x = (float)(i % map->cols) / (map->cols - 1);
// 		points[i].y = (float)(i / map->cols) / (map->rows - 1);
// 		if (range_z == 0)
// 			points[i].z = 0;
// 		else
// 			points[i].z = (float)(values_z_color[i].z - map->z_min) / range_z;
// 		i++;
// 	}
// }

// t_point2d	*prepare_iso_points(const t_map *map, t_point2d window_size)
// {
// 	t_point3d	*points;
// 	t_point2d	*iso_points;

// 	points = malloc(map->rows * map->cols * sizeof(t_point3d));
// 	if (!points)
// 	{
// 		handle_error("Memory allocation failed for points.");
// 		return (NULL);
// 	}
// 	iso_points = malloc(map->rows * map->cols * sizeof(t_point2d));
// 	if (!iso_points)
// 	{
// 		free(points);
// 		handle_error("Memory allocation failed for iso_points.");
// 		return (NULL);
// 	}
// 	populate_normalise_3d_points(points, map);
// 	to_pixel_coords(map, points, iso_points, window_size);
// 	free(points);
// 	return (iso_points);
// }

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