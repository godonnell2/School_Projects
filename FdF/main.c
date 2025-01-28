/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 20:46:05 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
The three-dimensional space is represented in two dimensions.
The angles between the axes are equal (typically 120 degrees).
The x, y, and z coordinates are transformed to give a sense of depth.
*/

static void	initialize_context(t_mlx_context *ctx, t_data *img, int width,
		int height)
{
	ctx->mlx = mlx_init();
	ctx->mlx_win = mlx_new_window(ctx->mlx, width, height,
			"This is my map on tv");
	img->img = mlx_new_image(ctx->mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static void	render_edge(t_data *img, t_edge *edge, t_map *map,
		t_point2d *iso_points)
{
	t_point2d	start;
	t_point2d	end;
	t_line		line;

	if (edge->start < 0 || edge->start >= map->cols * map->rows || edge->end < 0
		|| edge->end >= map->cols * map->rows)
		handle_error("invalid edges");
	start = iso_points[edge->start];
	end = iso_points[edge->end];
	if (start.x == end.x && start.y == end.y)
		return ;
	line.x0 = start.x;
	line.y0 = start.y;
	line.x1 = end.x;
	line.y1 = end.y;
	line.color = map->map_array[edge->start].color;
	draw_line(img, &line);
}

static void	render_edges(t_data *img, t_map *map, t_point2d *iso_points)
{
	int		edges_count;
	t_edge	*edges;
	int		i;

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

static char	*read_and_init_map(int argc, char **argv, t_map *map,
		int default_colour)
{
	char	*buffer;

	if (argc < 2)
		handle_error("Usage: <program_name> <map_file>");
	buffer = read_file_to_buffer(argv[1]);
	if (!buffer)
		handle_error("buffer read error");
	determine_dimensions(buffer, map);
	map->map_array = read_map_into_array(map, buffer, default_colour);
	if (!map->map_array)
		free(buffer);
	return (buffer);
}

int	main(int argc, char **argv)
{
	t_app	app;
	char	*buffer;
	int		default_colour;

	app.window_width = 1100;
	app.window_height = 800;
	default_colour = 0xFFFFFF;
	buffer = read_and_init_map(argc, argv, &app.map, default_colour);
	app.map.map_array = read_map_into_array(&app.map, buffer, default_colour);
	if (!app.map.map_array)
		free(buffer);
	find_min_max(app.map.map_array, app.map.rows * app.map.cols, &app.map);
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