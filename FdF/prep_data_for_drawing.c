/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:07:08 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 16:42:19 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
void	find_min_max(float *array, int array_size, t_map *map)
{
	int	i;

	if (array_size <= 0)
	{
		map->z_min = 0;
		map->z_max = 0;
		   handle_error("Array size is 0 or negative. Setting min and max to 0.\n");
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


// so basically this is how we drop the z axis
// because screens dont have a z axis
// Retrieve the 3D coordinates from the points array
// Apply the isometric projection formula
// 0.523599 radians = 30 degrees
// Store the resulting 2D point in the iso_points array
// x is indepent of the z interesting interseting 
 //30° rotation.
// need to invert y coordinate   iso_y = window_height - iso_y; he origin (0, 0) is the upper left corner of the window,
//  the x and y axis respectivelyInversion of Y-Axis: 
// etric projection of a 3D point  (x,y,z) onto a 2D plane involves a rotation of the point in 3D space. 
//  Since the y-axis in MLX points down, you may need to invert the y-coordinate after 
//  calculating the isometric y-coordinate.
//  The formula you're using is a simplified version of this transformation:

// iso_x = (x - y) * cos(θ)
// iso_y = (x + y) * sin(θ) - z
 

void	convert_to_isometric(t_map *map, t_point3d *points,
		t_point2d *iso_points, int window_height)
{
	float	iso_x;
	float	iso_y;
	int		i;
(void) window_height;
	i = 0;
	while (i < map->rows * map->cols)
	{
		
		iso_x = (points[i].x - points[i].y) * cos(0.523599);
		iso_y = (points[i].x + points[i].y) * sin(0.523599) - (points[i].z/10);

		iso_points[i].x = iso_x;
		iso_points[i].y = iso_y;
		
		i++;
	}
}

// Center horizontally
// Center vertically
#include <stdio.h>
void	scale_and_offset_points(t_point2d *iso_points, t_map *map,
		int window_width, int window_height)
{
	
	int		total_points;
	float	scale_factor;
	int		offset_x;
	int		offset_y;
	int		i;

	total_points = map->cols * map->rows;


  scale_factor = fmin(window_width / 1.6f, window_height / 1.6f);

	offset_x = window_width / 2;
	offset_y = window_height / 4;

	i = 0;
	while (i < total_points)
	{
		iso_points[i].x *= scale_factor;
		iso_points[i].y *= scale_factor;
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
// void	populate_edges(t_map *map, t_edge **edges, int *edges_count)
// {
// 	int	total_edges;
// 	int	y;
// 	int	x;
// 	int	current_index;

// 	total_edges = (map->cols - 1) * map->rows + (map->rows - 1) * map->cols;
// 	*edges = malloc(total_edges * sizeof(t_edge));
// 	if (*edges == NULL)
// 	{
// 		ft_printf(stderr, "Memory allocation failed for edges.\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	*edges_count = 0;
// 	y = 0;
// 	while (y < map->rows)
// 	{
// 		x = 0;
// 		while (x < map->cols)
// 		{
// 			current_index = y * map->cols + x;
// 			if (x < map->cols - 1)
// 			{
// 				(*edges)[*edges_count].start = current_index;
// 				(*edges)[*edges_count].end = current_index + 1;
// 				(*edges_count)++;
// 			}
// 			if (y < map->rows - 1)
// 			{
// 				(*edges)[*edges_count].start = current_index;
// 				(*edges)[*edges_count].end = current_index + map->cols;
// 				(*edges_count)++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

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