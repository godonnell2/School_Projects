/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymouse_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:21:19 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/29 21:13:12 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

void	free_iso_points(t_app *app)
{
	if (app->iso_points)
	{
		free(app->iso_points);
		app->iso_points = NULL;
	}
}

void	free_map_array(t_app *app)
{
	if (app->map.values_z_color)
	{
		free(app->map.values_z_color);
		app->map.values_z_color = NULL;
	}
}

void	destroy_window_and_image(t_app *app)
{
	if (app->ctx.mlx_win)
	{
		mlx_destroy_window(app->ctx.mlx, app->ctx.mlx_win);
		app->ctx.mlx_win = NULL;
	}
	if (app->img.img)
	{
		mlx_destroy_image(app->ctx.mlx, app->img.img);
		app->img.img = NULL;
	}
}

int	handle_exit(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_error("Exiting...");
	free_iso_points(app);
	free_map_array(app);
	destroy_window_and_image(app);
	exit(0);
}

// 65307 is the keycode for ESC in MLX on Linux //53 mac
int	handle_keypress(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
	{
		handle_exit(param);
	}
	return (0);
}
