/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymouse_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:21:19 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 17:35:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	handle_exit(void *param)
{
	t_app	*app;

	printf("Exiting...\n");
	app = (t_app *)param;

	// Destroy the window
	if (app->ctx.mlx_win)
		mlx_destroy_window(app->ctx.mlx, app->ctx.mlx_win);

	// Free allocated resources
	if (app->iso_points)
		free(app->iso_points);
	if (app->map_array)
		free(app->map_array);

	// Exit the program
	exit(0);
}
// 65307 is the keycode for ESC in MLX on Linux //53 mac
int	handle_keypress(int keycode, void *param)
{
	printf("keycode=%d\n", keycode);
	if (keycode == 65307 || keycode == 53)
	{
		handle_exit(param);
	}
	return (0);
}
