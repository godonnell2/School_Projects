/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 17:39:32 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	initialize_context(t_mlx_context *ctx, t_data *img, int width,
		int height)
{
	ctx->mlx = mlx_init();
	ctx->mlx_win = mlx_new_window(ctx->mlx, width, height, "Hello world!");
	img->img = mlx_new_image(ctx->mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static t_point2d	*prepare_iso_points(t_map *map, long *map_array, int width,
		int height)
{
	t_point3d	*points;
	t_point2d	*iso_points;

	points = malloc(map->rows * map->cols * sizeof(t_point3d));
	iso_points = calloc(map->rows * map->cols, sizeof(t_point2d));
	if (!points || !iso_points)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	generate_3d_points(map, map_array, points);
	convert_to_isometric(map, points, iso_points);
	scale_and_offset_points(iso_points, map, width, height);
	free(points);
	return (iso_points);
}

static void	render_edge(t_data *img, t_edge *edge, t_map *map,
		t_point2d *iso_points)
{
	t_point2d	start;
	t_point2d	end;
	t_line		line;

	if (edge->start < 0 || edge->start >= map->cols * map->rows || edge->end < 0
		|| edge->end >= map->cols * map->rows)
	{
		fprintf(stderr, "edge start=%d, end=%d\n", edge->start, edge->end);
		return ;
	}
	start = iso_points[edge->start];
	end = iso_points[edge->end];
	line.x0 = start.x;
	line.y0 = start.y;
	line.x1 = end.x;
	line.y1 = end.y;
	line.color = 0x00FF0000;
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

int	main(void)
{
	t_app		app;
	//long		*map_array;
	//t_point2d	*iso_points;
	char		*buffer;

	app.window_width = 1200;
	app.window_height = 900;
	buffer = read_file_to_buffer("test_maps/basictest.fdf");
	determine_dimensions(buffer, &app.map);
	app.map_array = read_map_into_array(&app.map, buffer);
	app.iso_points = prepare_iso_points(&app.map, app.map_array, app.window_width,
			app.window_height);
	initialize_context(&app.ctx, &app.img, app.window_width, app.window_height);
	render_edges(&app.img, &app.map, app.iso_points);
	mlx_put_image_to_window(app.ctx.mlx, app.ctx.mlx_win, app.img.img, 0, 0);
	mlx_hook(app.ctx.mlx_win, 17, 0, handle_exit, &app.ctx);
	mlx_key_hook(app.ctx.mlx_win, handle_keypress, &app.ctx);
	mlx_loop(app.ctx.mlx);
	return (0);
}
// Specialised event handlers
// int	main(void)
// {
// 	t_data			img;
// 	t_mlx_context	ctx;
// 	char			*buffer;
// 	t_map			map;
// 	long			*map_array;
// 	int				array_size;
// 	t_point3d		*points;
// 	t_point2d		*iso_points;
// 	t_point2d		start;
// 	t_point2d		end;
// 	int				window_width;
// 	int				window_height;
// 	int				edges_count;

// 	buffer = read_file_to_buffer("test_maps/basictest.fdf");
// 	determine_dimensions(buffer, &map);
// 	map_array = read_map_into_array(&map, buffer); // PRINTING CORRECTLY
// 	array_size = map.rows * map.cols;
// 	find_min_max(map_array, array_size, &map);
// 	points = malloc(map.rows * map.cols * sizeof(t_point3d));
// 	generate_3d_points(&map, map_array, points); // PRINTING CORRECTLY
// 	iso_points = calloc(map.rows * map.cols, sizeof(t_point2d));
// 	window_width = 1200;
// 	window_height = 900;
// 	convert_to_isometric(&map, points, iso_points);
// 	scale_and_offset_points(iso_points, &map, window_width, window_height);
// 	ctx.mlx = mlx_init();
// 	ctx.mlx_win = mlx_new_window(ctx.mlx, window_width, window_height,
// 			"Hello world!");
// 	img.img = mlx_new_image(ctx.mlx, window_width, window_height);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	//  draw_line(&img, 10, 220, 10, 320, 0x00FF0000);
// 	printf("Total points in iso_points: %d\n", map.cols * map.rows);
// 	for (int i = 0; i < map.cols * map.rows; i++)
// 	{
// 		printf("iso_points[%d]: (x: %f, y: %f)\n", i, iso_points[i].x,
// 			iso_points[i].y);
// 	}
// 	t_edge *edges = NULL; // Pointer for dynamically allocated edges
// 	edges_count = 0;
// 	populate_edges(&map, &edges, &edges_count);
// 	// Draw lines based on edges
// 	for (int i = 0; i < edges_count; i++)
// 	{
// 		if (edges[i].start < 0 || edges[i].start >= map.cols * map.rows
// 			|| edges[i].end < 0 || edges[i].end >= map.cols * map.rows)
// 		{
// 			fprintf(stderr, "Invalid edge indices: start=%d, end=%d\n",
// 				edges[i].start, edges[i].end);
// 			continue ;
// 		}
// 		start = iso_points[edges[i].start];
// 		end = iso_points[edges[i].end];
// 		t_line line = {start.x, start.y, end.x, end.y, 0x00FF0000};
// 		draw_line(&img, &line);
// 	}
// 	mlx_put_image_to_window(ctx.mlx, ctx.mlx_win, img.img, 0, 0);
// 	mlx_hook(ctx.mlx_win, 17, 0, handle_exit, &ctx);
// 	mlx_key_hook(ctx.mlx_win, handle_keypress, &ctx);
// 	free(points);
// 	free(iso_points);
// 	free(edges);
// 	// NEED TO BE AT END!!!
// 	mlx_loop(ctx.mlx);
// }

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