/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/07/30 09:35:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// app var means it holds everything i need at run time

void	init_renderer(t_data *app, int screen_w, int screen_h)
{
	app->mlx->mlx_ptr = mlx_init();
	app->mlx->win_ptr = mlx_new_window(app->mlx->mlx_ptr, screen_w, screen_h,
			"cub3d");
	app->mlx->img_ptr = mlx_new_image(app->mlx->mlx_ptr, screen_w, screen_h);
	app->mlx->img_data = mlx_get_data_addr(app->mlx->img_ptr,
			&app->mlx->bits_per_pixel, &app->mlx->line_length,
			&app->mlx->endian);
	app->mlx->width = screen_w;
	app->mlx->height = screen_h;
}

//need tp include this !!!!!
void	destroy_renderer(t_data *app)
{
	if (app->mlx->img_ptr)
		mlx_destroy_image(app->mlx->mlx_ptr, app->mlx->img_ptr);
	if (app->mlx->win_ptr)
		mlx_destroy_window(app->mlx->mlx_ptr, app->mlx->win_ptr);
}

/*
rays is a static ptr only allocated once teh first tiem render frame runs
one ray per vertical column of the screen.
so however many pixels wide is how many rays
*/
/* High‑level routine you call each frame */


void	render_frame(t_data *app)
{
	static t_ray	*rays = NULL;

	if (!rays)
		rays = malloc(sizeof(*rays) * app->mlx->width);
	raycasting(app, rays, app->elem);
	draw_walls(app->mlx, rays, app->elem);
}


// W.  13) 
 // S  1)
// A  0) 
// D 2
// Left arrow  123)
// Right arrow 124
 // ESC  53)
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 13) 
		data->keys.w = 1;
	else if (keycode == 1) 
		data->keys.s = 1;
	else if (keycode == 0) 
		data->keys.a = 1;
	else if (keycode == 2) 
		data->keys.d = 1;
	else if (keycode == 123) 
		data->keys.left = 1;
	else if (keycode == 124) 
		data->keys.right = 1;
	else if (keycode == 53) 
		handle_close(data);
	return (0);
}

void	handle_movement(t_data *data)
{
	if (data->keys.w)
		move_forward(data->elem->map, &data->elem->player, MOVE_SPEED);
	if (data->keys.s)
		move_backward(data->elem->map, &data->elem->player, MOVE_SPEED);
	if (data->keys.a)
		move_left(data->elem->map, &data->elem->player, MOVE_SPEED);
	if (data->keys.d)
		move_right(data->elem->map, &data->elem->player, MOVE_SPEED);
	if (data->keys.left)
		rotate_left(&data->elem->player, ROTATE_SPEED);
	if (data->keys.right)
		rotate_right(&data->elem->player, ROTATE_SPEED);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

/*
 Think of your screen as a 2D grid of vertical slices (columns).
Each time you cast a ray (from left to right across your FOV), you calculate:

How far it traveled before hitting a wall.

What wall texture to draw.

How tall that vertical slice of wall should be on screen.

That “slice” = 1 column of pixels representing a wall at a specific angle.

Example:
If your screen is 800 pixels wide, and you cast 800 rays:

You’re calculating 800 vertical slices.

Each ray = 1 slice = 1 vertical column of pixels showing part of the wall.
*/