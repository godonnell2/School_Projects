/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymouse_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:21:19 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 06:22:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	handle_exit(void *param)
{
	t_mlx_context	*ctx;

	printf("exiting\n");
	ctx = (t_mlx_context *)param;
	if (ctx->mlx_win)
		mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	// Perform additional cleanup here if needed
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
