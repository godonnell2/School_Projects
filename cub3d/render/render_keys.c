/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/11 17:59:59 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// app var means it holds everything i need at run time
// need tp include this !!!!!
void	destroy_renderer(t_data *app)
{
	if (app->mlx->img_ptr)
		mlx_destroy_image(app->mlx->mlx_ptr, app->mlx->img_ptr);
	if (app->mlx->win_ptr)
		mlx_destroy_window(app->mlx->mlx_ptr, app->mlx->win_ptr);
}

void	clear_image(t_mlx *mlx, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			put_pixel(x, y, color, mlx);
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *app)
{
	static t_ray	*rays = NULL;

	if (app->mlx->img_ptr)
		mlx_destroy_image(app->mlx->mlx_ptr, app->mlx->img_ptr);
	app->mlx->img_ptr = mlx_new_image(app->mlx->mlx_ptr, app->mlx->width,
			app->mlx->height);
	if (!app->mlx->img_ptr)
		return ;
	app->mlx->img_data = mlx_get_data_addr(app->mlx->img_ptr,
			&app->mlx->bits_per_pixel, &app->mlx->line_length,
			&app->mlx->endian);
	clear_image(app->mlx, 0x000000);
	if (!rays)
		rays = malloc(sizeof(*rays) * app->mlx->width);
	raycasting(app, rays, app->elem);
	draw_walls(app->mlx, rays, app->elem);
}

// 'w' eycode == 119)
// printf("Key pressed: %d\n", keycode);
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	else if (keycode == 115)
		data->keys.s = 1;
	else if (keycode == 97)
		data->keys.a = 1;
	else if (keycode == 100)
		data->keys.d = 1;
	else if (keycode == 65361)
		data->keys.left = 1;
	else if (keycode == 65363)
		data->keys.right = 1;
	else if (keycode == 65362)
		data->keys.w = 1;
	else if (keycode == 65364)
		data->keys.s = 1;
	else if (keycode == 65307)
		handle_close(data);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == 65362)
		data->keys.w = 0;
	else if (keycode == KEY_S || keycode == 65364)
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
