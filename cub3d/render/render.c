/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/10 16:40:42 by gro-donn         ###   ########.fr       */
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
 // Destroy the previous image to prevent a memory leak
 // Create a new image for the current frame
 // Handle error
 // Get the address of the pixel data for the new image
 void clear_image(t_mlx *mlx, int color)
{
    for (int y = 0; y < mlx->height; y++)
        for (int x = 0; x < mlx->width; x++)
            put_pixel(x, y, color, mlx);
}

void	render_frame(t_data *app)
{
	static t_ray	*rays = NULL;

   
    if (app->mlx->img_ptr)
        mlx_destroy_image(app->mlx->mlx_ptr, app->mlx->img_ptr);

    app->mlx->img_ptr = mlx_new_image(app->mlx->mlx_ptr, app->mlx->width, app->mlx->height);
    if (!app->mlx->img_ptr)
        return; 


    app->mlx->img_data = mlx_get_data_addr(app->mlx->img_ptr, &app->mlx->bits_per_pixel, &app->mlx->line_length, &app->mlx->endian);

	clear_image(app->mlx, 0x000000); 
	if (!rays)
		rays = malloc(sizeof(*rays) * app->mlx->width);
	raycasting(app, rays, app->elem);
	draw_walls(app->mlx, rays, app->elem);
}

 // 'w' eycode == 119)          
int handle_keypress(int keycode, t_data *data)
{
    printf("Key pressed: %d\n", keycode);
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

int handle_keyrelease(int keycode, t_data *data)
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

