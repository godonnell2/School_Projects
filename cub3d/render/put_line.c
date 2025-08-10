/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:56 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/10 17:14:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// return int representing colour usally in agba 4byte int
// flattening a 2d arr into a 1d arr very common memory technique
// basically instead of having 2pts represent you have one 1pt to do it
// in row major order
// int	get_tex_pixel(t_texture *tex, int x, int y)
// {
// 	int	*data;

// 	data = (int *)tex->data;
// 	return (data[y * tex->width + x]);
// }
int get_tex_pixel(t_texture *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
    {
        printf("[ERROR] get_tex_pixel: coords out of range x=%d y=%d\n", x, y);
        return 0;
    }
    int bytes_per_pixel = tex->bits_per_pixel / 8;
    int offset = y * tex->line_length + x * bytes_per_pixel;

    unsigned char *pixel = (unsigned char *)(tex->data + offset);

    unsigned int color = 0;
    if (bytes_per_pixel == 4)
    {
        color = *(unsigned int *)pixel;
    }
    else if (bytes_per_pixel == 3)
    {
        color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);
    }
    else
    {
        printf("[ERROR] Unsupported bits_per_pixel: %d\n", tex->bits_per_pixel);
        return 0;
    }
    return color;
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
