/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:56 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/11 15:44:01 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// return int representing colour  
//top check prevents reading outside texture arr
// convert bits to bytes by /8 32-bit → 4 bytes per pixel (RGBA 
// Calculating the memory address of the pixel
// 3bits 24 bits per pixel ( rbg no alpha channel).
int get_tex_pixel(t_texture *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return 0;

    int bpp = tex->bits_per_pixel / 8;
    unsigned char *pixel = (unsigned char *)tex->data + y * tex->line_length + x * bpp;

    if (bpp == 4)
        return *(unsigned int *)pixel;
    if (bpp == 3)
        return pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);

    return 0;
}

void	put_pixel(int x, int y, int color, t_mlx *mlx)
{
	if (x < 0 || y < 0 || x >= mlx->width || y >= mlx->height)
		return;  
	int	offset;

	offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
	if (offset < 0 || offset >= mlx->height * mlx->line_length)
		return; 
	
	*(unsigned int *)(mlx->img_data + offset) = color;
}


void fill_column(t_mlx *mlx, int x, int y_start, int y_end, int color)
{
    int y = y_start;
    while (y < y_end)
    {
        put_pixel(x, y, color, mlx);
        y++;
    }
}
