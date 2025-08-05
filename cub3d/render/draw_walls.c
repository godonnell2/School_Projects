/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/05 18:04:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture *select_texture(t_cub_elements *app, t_ray *ray)
{
    if (ray->vertical_hit)
        return is_ray_facing(EAST, ray->angle) ? app->ea_text : app->we_text;
    else
        return is_ray_facing(NORTH, ray->angle) ? app->no_text : app->so_text;
}

int get_tex_x(t_ray *ray, t_texture *tex, t_map *map)
{
    double wallx;
    
    // Calculate wall hit position within the tile
    if (ray->vertical_hit)
        wallx = fmod(ray->hit[Y], map->tile_size);
    else
        wallx = fmod(ray->hit[X], map->tile_size);
    
    // Normalize to [0,1)
    wallx /= map->tile_size;
    
    int texx = (int)(wallx * tex->width);
    
    // Flip texture if needed
    if ((ray->vertical_hit && is_ray_facing(WEST, ray->angle)) ||
        (!ray->vertical_hit && is_ray_facing(SOUTH, ray->angle))) {
        texx = tex->width - texx - 1;
    }
    
    // Clamp to valid range
    if (texx < 0) texx = 0;
    if (texx >= tex->width) texx = tex->width - 1;
    
    return texx;
}

void draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice)
{
    double step = (double)tex->height / slice->line_h;
    double texpos = (slice->start - mlx->height / 2 + slice->line_h / 2) * step;
    
    for (int y = slice->start; y < slice->end; y++) {
        int texy = (int)texpos;
        if (texy < 0) texy = 0;
        if (texy >= tex->height) texy = tex->height - 1;
        
        int color = get_tex_pixel(tex, slice->texX, texy);
        put_pixel(slice->x, y, color, mlx);
        texpos += step;
    }
}

t_render_slice calculate_slice(t_mlx *mlx, t_ray *ray, int x, t_cub_elements *elem)
{
    t_render_slice slice;
    int start_end[2];
    
    // Correct for fisheye effect
    float corrected_dist = ray->dist * cos(ray->angle - elem->player.angle);
    
    // Calculate line height based on corrected distance
    int line_h = (mlx->height / corrected_dist);
    
    start_end[0] = -line_h / 2 + mlx->height / 2;
    if (start_end[0] < 0) start_end[0] = 0;
    
    start_end[1] = line_h / 2 + mlx->height / 2;
    if (start_end[1] >= mlx->height) start_end[1] = mlx->height - 1;
    
    t_texture *tex = select_texture(elem, ray);
    int texx = get_tex_x(ray, tex, elem->map);
    
    slice = (t_render_slice){
        .x = x,
        .texX = texx,
        .start = start_end[0],
        .end = start_end[1],
        .line_h = line_h
    };
    
    return slice;
}

void draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
    // Clear screen
    for (int y = 0; y < mlx->height; y++) {
        for (int x = 0; x < mlx->width; x++) {
            if (y < mlx->height / 2)
                put_pixel(x, y, elem->ceiling_color->hex_color, mlx);
            else
                put_pixel(x, y, elem->floor_color->hex_color, mlx);
        }
    }
    
    // Draw walls
    for (int x = 0; x < mlx->width; x++) {
        t_ray *ray = &rays[x];
        t_render_slice slice = calculate_slice(mlx, ray, x, elem);
        draw_wall_column(mlx, select_texture(elem, ray), &slice);
    }
    
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}