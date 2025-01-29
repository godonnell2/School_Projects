/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing_three.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:31:12 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/29 21:47:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// you have to bring z to zero before you start to get (0,1)
// which is why you minus min z
// float	*extract_z_values(t_map_point *values_z_color, int size)
// Normalize x, y to the [0, 1] range based on the number of rows and columns
void	populate_3d_points(t_point3d *points, const t_map *map)
{
	float		range_z;
	int			index;
	t_map_point	*values_z_color;

	values_z_color = map->values_z_color;
	range_z = map->z_max - map->z_min;
	index = 0;
	while (index < (map->rows * map->cols))
	{
		points[index].x = (float)(index % map->rows) / (map->cols - 1);
		points[index].y = (float)(index / map->rows) / (map->rows - 1);
		if (range_z == 0)
			points[index].z = 0;
		else
			points[index].z = (float)(values_z_color[index].z - map->z_min)
				/ range_z;
		index++;
	}
}

// Normalize x, y to the [0,1] range based on the number of rows and cols
// eg points[index].x = (float)x / (map->cols - 1);

static t_point3d	*allocate_points(const t_map *map)
{
	t_point3d	*points;

	points = malloc(map->rows * map->cols * sizeof(t_point3d));
	if (!points)
		handle_error("Memory allocation failed for points.");
	return (points);
}

t_point2d	*prepare_iso_points(const t_map *map, int window_width,
		int window_height)
{
	t_point3d	*points;
	t_point2d	*iso_points;

	points = allocate_points(map);
	if (!points)
		return (NULL);
	iso_points = malloc(map->rows * map->cols * sizeof(t_point2d));
	if (!iso_points)
	{
		free(points);
		handle_error("Memory allocation failed for iso_points.");
		return (NULL);
	}
	populate_3d_points(points, map);
	convert_to_isometric(map, points, iso_points);
	scale_and_offset_points(iso_points, map, window_width, window_height);
	free(points);
	return (iso_points);
}
