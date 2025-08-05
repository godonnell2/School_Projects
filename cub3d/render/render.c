/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/05 18:17:56 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// app var means it holds everything i need at run time
/*
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
*/
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


void render_frame(t_data *app)
{
    static t_ray *rays = NULL;
    
    if (!rays) rays = malloc(sizeof(t_ray) * app->mlx->width);
    
    // Clear image buffer
    ft_memset(app->mlx->img_data, 0, 
              app->mlx->height * app->mlx->line_length);
    
    raycasting(app, rays, app->elem);
    draw_walls(app->mlx, rays, app->elem);
}

int handle_keypress(int keycode, t_data *data)
{
	    printf("Key pressed: %d\n", keycode);
    if (keycode == KEY_W) data->keys.w = 1;
    else if (keycode == KEY_S) data->keys.s = 1;
    else if (keycode == KEY_A) data->keys.a = 1;
    else if (keycode == KEY_D) data->keys.d = 1;
    else if (keycode == KEY_LEFT) data->keys.left = 1;
    else if (keycode == KEY_RIGHT) data->keys.right = 1;
    else if (keycode == KEY_ESC) handle_close(data);
    
    return 0;
}

int handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == KEY_W) data->keys.w = 0;
    else if (keycode == KEY_S) data->keys.s = 0;
    else if (keycode == KEY_A) data->keys.a = 0;
    else if (keycode == KEY_D) data->keys.d = 0;
    else if (keycode == KEY_LEFT) data->keys.left = 0;
    else if (keycode == KEY_RIGHT) data->keys.right = 0;
    
    return 0;
}
/*
 Think of your screen as a 2D grid of vertical slices (columns).
Each time you cast a ray (from left to right across your FOV), you calculate:

How far it traveled before hitting a wall.

What wall texture to draw.

How tall that vertical slice of wall should be on screen.

That “slice” = 1 column of pixels representing a wall at a specific angle.
If your screen is 800 pixels wide, and you cast 800 rays:
You’re calculating 800 vertical slices.
Each ray = 1 slice = 1 vertical column of pixels showing part of the wall.
*/