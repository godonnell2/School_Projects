/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/14 13:27:14 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "fdf.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// bresenhams line algorithm
void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, color); 

		if (x0 == x1 && y0 == y1) 
			break;

		int e2 = err * 2;

		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int handle_exit(void *param)
{
	printf("exiting\n");
    t_mlx_context *ctx = (t_mlx_context *)param;

    if (ctx->mlx_win)
        mlx_destroy_window(ctx->mlx, ctx->mlx_win);

    // Perform additional cleanup here if needed

    exit(0);
}
// 65307 is the keycode for ESC in MLX on Linux (X11)
int handle_keypress(int keycode, void *param)
{
	printf("keycode=%d\n", keycode);
	//53 mac
    if (keycode == 65307 || keycode == 53) 
    {
        handle_exit(param);
    }
    return (0);
}


int	main(void)
{
	//void	*mlx;
	//void	*mlx_win;
	t_data	img;
	t_mlx_context ctx;
	
	ctx.mlx = mlx_init();
	ctx.mlx_win = mlx_new_window(ctx.mlx, 500, 350, "Hello world!");
	img.img = mlx_new_image(ctx.mlx, 500, 350);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
								
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	draw_line(&img, 10, 220, 10, 320, 0x00FF0000);
	draw_line(&img, 10, 220, 100, 20, 0x00FF0000);
	draw_line(&img, 100, 20, 10, 320, 0x00FF0000);
	mlx_put_image_to_window(ctx.mlx, ctx.mlx_win, img.img, 0, 0);
	
	

	 // Hook event handlers
    mlx_hook(ctx.mlx_win, 17, 0, handle_exit, &ctx);      // Close button
    mlx_key_hook(ctx.mlx_win, handle_keypress, &ctx);     // Key press

	// NEED TO BE AT END!!!
	mlx_loop(ctx.mlx);
}
//a triangle is a shape where three lines connect  
//2 lines meet at each point 