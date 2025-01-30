/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data_for_drawing_three.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:31:12 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/30 21:56:56 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// you have to bring z to zero before you start to get (0,1)
// which is why you minus min z
// float	*extract_z_values(t_map_point *values_z_color, int size)
// Normalize x, y to the [0,1] range based on the number of rows and cols

// static void debug_index (t_point3d *points, int array_size, int index)
// {
// 	int i = 0;
// 	while(i < array_size)
// 	{
// 	printf("point:%d , x:%.2f, y:%.2f, ,index:%d\n, ", i, points[i].x,
// points[i].y, index);
// 	i++;
// 	}

// }

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

t_point2d	*prepare_iso_points(const t_map *map, int window_width,
		int window_height)
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
	to_pixel_coords(map, points, iso_points);
	scale_and_offset_points(iso_points, map, window_width, window_height);
	free(points);
	return (iso_points);
}
