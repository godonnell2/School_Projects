/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/11 17:34:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	*select_texture(t_cub_elements *app, t_ray *ray)
{
	if (ray->vertical_hit)
	{
		if (is_ray_facing(EAST, ray->angle))
			return (app->ea_text);
		else
			return (app->we_text);
	}
	else
	{
		if (is_ray_facing(NORTH, ray->angle))
			return (app->no_text);
		else
			return (app->so_text);
	}
}

/*
then wallX is computed using the x axis.
Normalize to 0–1 ie get teh fractional part  of the width
then you find that part of the texture
*/

int get_tex_x(t_ray *ray, t_texture *tex)
{
    double wall_hit_pos; 
    int tex_x;

    if (ray->vertical_hit)
        wall_hit_pos = ray->hit[Y];  
    else
        wall_hit_pos = ray->hit[X];  

    wall_hit_pos -= floor(wall_hit_pos / TILE_SIZE) * TILE_SIZE;

    if ((ray->vertical_hit && is_ray_facing(WEST, ray->angle)) ||
        (!ray->vertical_hit && is_ray_facing(NORTH, ray->angle)))
    {
        wall_hit_pos = TILE_SIZE - wall_hit_pos;
    }

    tex_x = (int)((wall_hit_pos / TILE_SIZE) * tex->width);

    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;

    return tex_x;
}

t_render_slice calculate_slice(t_mlx *mlx, t_ray *ray, int col, t_cub_elements *elem)
{
    t_render_slice slice;
    double corrected_dist;
    double dist_proj_plane;
    double raw_line_h;   
    int draw_line_h;     
    int start, end;
    t_texture *tex;
    int texx;

   
    corrected_dist = (double)ray->distance * cos(ray->angle - elem->player.angle);
    if (corrected_dist <= 0.00001)
        corrected_dist = 0.00001;

    dist_proj_plane = ((double)mlx->width / 2.0) / tan(FOV / 2.0);

    raw_line_h = ((double)TILE_SIZE / corrected_dist) * dist_proj_plane;

    draw_line_h = (int)raw_line_h;
    if (draw_line_h < 1) draw_line_h = 1;
    if (draw_line_h > mlx->height) draw_line_h = mlx->height;

    start = (mlx->height / 2) - (draw_line_h / 2);
    if (start < 0) start = 0;
    end = start + draw_line_h;
    if (end >= mlx->height) end = mlx->height - 1;

    tex = select_texture(elem, ray);
    texx = get_tex_x(ray, tex);

   
    slice.x = col;
    slice.texX = texx;
    slice.start = start;
    slice.end = end;
    slice.line_h = draw_line_h;  
    slice.line_h_d = raw_line_h;  

    return slice;
}

void draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice,
                      t_cub_elements *elem)
{
    double step;
    double tex_y;
    int y;

    int start = slice->start;
    int end = slice->end;

    if (start < 0) start = 0;
    if (end > mlx->height) end = mlx->height;

    for (y = 0; y < start; y++) 
        put_pixel(slice->x, y, elem->ceiling_color->hex_color, mlx);

    step = (double)tex->height / slice->line_h_d;
    tex_y = (start - (mlx->height / 2) + (slice->line_h_d / 2)) * step;

    for (y = start; y < end; y++)
    {
        int tex_y_int = (int)tex_y;
        if (tex_y_int < 0) tex_y_int = 0;
        if (tex_y_int >= tex->height) tex_y_int = tex->height - 1;

        int color = get_tex_pixel(tex, slice->texX, tex_y_int);
        put_pixel(slice->x, y, color, mlx);
        tex_y += step;
    }
    for (y = end; y < mlx->height; y++)
        put_pixel(slice->x, y, elem->floor_color->hex_color, mlx);
}

void draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
   int x = 0;
    while (x < mlx->width)
    {
        t_ray *ray = &rays[x];
        t_render_slice slice = calculate_slice(mlx, ray, x, elem);
        t_texture *tex = select_texture(elem, ray);

        draw_wall_column(mlx, tex, &slice, elem);
        x++;
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}