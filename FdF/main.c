/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/31 10:29:16 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
The three-dimensional space is represented in two dimensions.
The angles between the axes are equal (typically 120 degrees).
The x, y, and z coordinates are transformed to give a sense of depth.
*/

static void	initialize_context(t_mlx_context *ctx, t_data *img,
		t_point2d window_size)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		handle_error("Error: Failed to initialize mlx");
	ctx->mlx_win = mlx_new_window(ctx->mlx, window_size.x, window_size.y,
			"This is my map on tv");
	img->img = mlx_new_image(ctx->mlx, window_size.x, window_size.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static void	render_edge(t_data *img, t_edge *edge, t_map *map,
		t_point2d *iso_points)
{
	t_point2d	start;
	t_point2d	end;

	if (edge->start < 0 || edge->start >= map->cols * map->rows || edge->end < 0
		|| edge->end >= map->cols * map->rows)
		handle_error("invalid edges");
	start = iso_points[edge->start];
	end = iso_points[edge->end];
	if (start.x == end.x && start.y == end.y)
		return ;
	draw_line(img, start, end, map->values_z_color[edge->start].color);
}

static void	render_edges(t_data *img, t_map *map, t_point2d *iso_points)
{
	int		edges_count;
	t_edge	*edges;
	int		i;

	edges_count = (map->cols - 1) * map->rows + (map->rows - 1) * map->cols;
	edges = populate_edges(map, edges_count);
	if (!edges)
	{
		handle_error("Memory allocation failed for  populate edges.\n");
	}
	i = 0;
	while (i < edges_count)
	{
		render_edge(img, &edges[i], map, iso_points);
		i++;
	}
	free(edges);
}

static t_map	read_and_init_map(int argc, char **argv, int default_colour)
{
	char	*buffer;
	t_map	map;

	if (argc < 2)
		handle_error("Usage: <program_name> <map_file>");
	buffer = read_file_to_buffer(argv[1]);
	if (!buffer)
		handle_error("buffer read error");
	determine_dimensions(buffer, &map);
	if (map.cols == 0 || map.rows == 0)
	{
		free(buffer);
		handle_error("There's no point, no points\n");
	}
	map.values_z_color = read_z_color(map.cols * map.rows, buffer,
			default_colour);
	free(buffer);
	find_min_max(&map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_app	app;
	int		default_colour;

	app.window_size.x = 1100;
	app.window_size.y = 800;
	default_colour = 0xFFFFFF;
	app.map = read_and_init_map(argc, argv, default_colour);
	app.iso_points = prepare_iso_points(&app.map, app.window_size);
	initialize_context(&app.ctx, &app.img, app.window_size);
	render_edges(&app.img, &app.map, app.iso_points);
	mlx_put_image_to_window(app.ctx.mlx, app.ctx.mlx_win, app.img.img, 0, 0);
	mlx_hook(app.ctx.mlx_win, 17, 0, handle_exit, &app);
	mlx_key_hook(app.ctx.mlx_win, handle_keypress, &app);
	mlx_loop(app.ctx.mlx);
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