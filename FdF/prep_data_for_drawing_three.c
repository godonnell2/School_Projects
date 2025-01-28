/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing_three.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:31:12 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 20:37:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// you have to bring z to zero before you start to get (0,1)
// which is why you minus min z
// float	*extract_z_values(t_map_point *map_array, int size)
// Normalize x, y to the [0, 1] range based on the number of rows and columns
void	populate_z_values(t_point3d *points, t_map_point *map_array, t_map *map)
{
	float	range_z;
	int		index;
	int		y;
	int		x;

	range_z = map->z_max - map->z_min;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			index = y * map->cols + x;
			points[index].x = (float)x / (map->cols - 1);
			points[index].y = (float)y / (map->rows - 1);
			if (range_z == 0)
				points[index].z = 0;
			else
				points[index].z = (float)(map_array[index].z - map->z_min)
					/ range_z;
			x++;
		}
		y++;
	}
}

// Normalize x, y to the [0,1] range based on the number of rows and cols
// eg points[index].x = (float)x / (map->cols - 1);

static t_point3d	*allocate_points(t_map *map)
{
	t_point3d	*points;

	points = malloc(map->rows * map->cols * sizeof(t_point3d));
	if (!points)
		handle_error("Memory allocation failed for points.");
	return (points);
}

static t_point2d	*allocate_iso_points(t_map *map)
{
	t_point2d	*iso_points;

	iso_points = calloc(map->rows * map->cols, sizeof(t_point2d));
	if (!iso_points)
		handle_error("Memory allocation failed for iso_points.");
	return (iso_points);
}

static void	populate_coordinates(t_point3d *points, t_map *map)
{
	int	index;
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			index = y * map->cols + x;
			points[index].x = (float)x / (map->cols - 1);
			points[index].y = (float)y / (map->rows - 1);
			x++;
		}
		y++;
	}
}

t_point2d	*prepare_iso_points(t_map *map, t_map_point *map_array, int width,
		int height)
{
	t_point3d	*points;
	t_point2d	*iso_points;

	points = allocate_points(map);
	if (!points)
		return (NULL);
	iso_points = allocate_iso_points(map);
	if (!iso_points)
	{
		free(points);
		return (NULL);
	}
	populate_z_values(points, map_array, map);
	populate_coordinates(points, map);
	convert_to_isometric(map, points, iso_points);
	scale_and_offset_points(iso_points, map, width, height);
	free(points);
	return (iso_points);
}
