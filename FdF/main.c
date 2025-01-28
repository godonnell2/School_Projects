/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 16:40:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
/*
The three-dimensional space is represented in two dimensions.
The angles between the axes are equal (typically 120 degrees).
The x, y, and z coordinates are transformed to give a sense of depth.

*/

static void initialize_context(t_mlx_context *ctx, t_data *img, int width,
							   int height)
{
	ctx->mlx = mlx_init();
	ctx->mlx_win = mlx_new_window(ctx->mlx, width, height, "This is my map on tv");
	img->img = mlx_new_image(ctx->mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								  &img->line_length, &img->endian);
}

// you have to bring z to zero before you start to get (0,1)
// which is why you minus min z
// here we are just creating an arr of z values from the map array of tpooint structures
float *extract_z_values(t_map_point *map_array, int size)
{
    float *z_values = malloc(size * sizeof(float));
    if (!z_values)
    {
        handle_error("Memory allocation failed for z_values.");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        z_values[i] = map_array[i].z; 
    }

    return z_values;
}


 // Normalize x, y to the [0, 1] range based on the number of rows and columns
void populate_z_values(t_point3d *points, t_map_point *map_array, t_map *map)
{

    float min_z = map->z_min;
    float max_z = map->z_max;
    float range_z = max_z - min_z;

	
    for (int y = 0; y < map->rows; y++)
    {
        for (int x = 0; x < map->cols; x++)
        {
            int index = y * map->cols + x;

           
            points[index].x = (float)x / (map->cols - 1); 
            points[index].y = (float)y / (map->rows - 1);

            // Normalize z based on the range of z values
            if (range_z == 0) {
                points[index].z = 0;  // Or you could set it to another default value if needed
            } else {
                points[index].z = (float)(map_array[index].z - min_z) / range_z;
            }

        }
    }
}
static t_point2d *prepare_iso_points(t_map *map, t_map_point *map_array, int width, int height)
{
	t_point3d *points;
	t_point2d *iso_points;

	t_app app;
	app.window_width = 1100;
	app.window_height = 800;
	
	points = malloc(map->rows * map->cols * sizeof(t_point3d));
	if (!points)
    {
        handle_error("Memory allocation failed for points.");
		return NULL;
    }

	iso_points = calloc(map->rows * map->cols, sizeof(t_point2d));
	if (!iso_points)
    {
        free(points); 
        handle_error("Memory allocation failed for iso_points.");
		return NULL;
    }
	 
    populate_z_values(points, map_array, map);

    for (int y = 0; y < map->rows; y++)
    {
        for (int x = 0; x < map->cols; x++)
        {
            int index = y * map->cols + x;

            // Normalize x, y to the [0, 1] range based on the number of rows and columns
            points[index].x = (float)x / (map->cols - 1); 
            points[index].y = (float)y / (map->rows - 1);

        }
    }

	convert_to_isometric(map, points, iso_points, app.window_height);
	scale_and_offset_points(iso_points, map, width, height);
	
	free(points);

	return iso_points;
}


static void render_edge(t_data *img, t_edge *edge, t_map *map,
						t_point2d *iso_points)
{
	t_point2d start;
	t_point2d end;
	t_line line;

	if (edge->start < 0 || edge->start >= map->cols * map->rows || edge->end < 0 || edge->end >= map->cols * map->rows)
	{
		handle_error("invalid edges");
	}
	start = iso_points[edge->start];
	end = iso_points[edge->end];
	if (start.x == end.x && start.y == end.y)
	{
		return;
	}


	line.x0 = start.x;
	line.y0 = start.y;
	line.x1 = end.x;
	line.y1 = end.y;
	line.color = map->map_array[edge->start].color;
	draw_line(img, &line);
}

static void render_edges(t_data *img, t_map *map, t_point2d *iso_points)
{
	int edges_count;
	t_edge *edges;
	int i;

	edges = NULL;
	populate_edges(map, &edges, &edges_count);
	i = 0;
	while (i < edges_count)
	{
		render_edge(img, &edges[i], map, iso_points);
		i++;
	}
	free(edges);
}

int main(int argc, char **argv)
{
	t_app app;
	app.window_width = 1100;
	app.window_height = 800;
	
	char *buffer;
	int default_colour = 0xFFFFFF;
	if (argc < 2)
	{
		handle_error("Usage: <program_name> <map_file>");
		return 1;
	}
	
	buffer = read_file_to_buffer(argv[1]);
	if (!buffer)
	{
		handle_error("buffer read error");
	}
	determine_dimensions(buffer, &app.map);
	app.map.map_array = read_map_into_array(&app.map, buffer, default_colour);

	if (!app.map.map_array)
	{
		free(buffer);
		return 1;
	}

	float *z_values = extract_z_values(app.map.map_array, app.map.rows * app.map.cols);
    if (!z_values)
    {
        free(buffer);
        free(app.map.map_array);
        return 1;
    }

    find_min_max(z_values, app.map.rows * app.map.cols, &app.map);
    free(z_values);

	app.iso_points = prepare_iso_points(&app.map, app.map.map_array,
										app.window_width, app.window_height);
	initialize_context(&app.ctx, &app.img, app.window_width, app.window_height);
	render_edges(&app.img, &app.map, app.iso_points);
	mlx_put_image_to_window(app.ctx.mlx, app.ctx.mlx_win, app.img.img, 0, 0);
	mlx_hook(app.ctx.mlx_win, 17, 0, handle_exit, &app.ctx);
	mlx_key_hook(app.ctx.mlx_win, handle_keypress, &app.ctx);
	mlx_loop(app.ctx.mlx);
	free(buffer);
	free(app.map.map_array);
	return (0);
}


// 17 = DestroyNotify    NAME OF LIB used by minilibx for linux = x11 x.h
// OS has told x that the window close button has been pressed
// 0 is the mask it says no mask! look at ALL bits
// (otherwise can bit shift for more specificity)
// a triangle is a shape where three lines connect
// 2 lines meet at each point

/*
Isometric Projection Formula
In isometric projection:

Orthographic: No perspective or distortion; parallel lines remain parallel.
 Views the object straight-on from one axis (e.g., top, front, side).
 No foreshortening unless explicitly specified for oblique views.
 Isometric: Maintains proportions without depth distortion, using equal angles
 between axes.
 Rotates the object so that all three axes (X, Y, Z) are equally foreshortened.
 The angle between axes in 2D is 120
 Shows a pseudo-3D view where all three dimensions are visible.
 Applies equal foreshortening along all three axes.
 .
Perspective: Includes depth distortion to simulate the human eye.




*/