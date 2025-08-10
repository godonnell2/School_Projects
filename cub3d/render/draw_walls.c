/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/10 17:09:29 by gro-donn         ###   ########.fr       */
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
Calculate where exactly the ray hit the wall in world space
If the ray hit a vertical wall, then the X coordinate is fixed
(you hit a vertical plane), and the Y coordinate changes —
so we calculate wallX using the y axis.
The player's Y-coordinate.
ray->dist: The distance from the player to the hit point on the wall.
If the ray hit a horizontal wall,
then wallX is computed using the x axis.
Normalize to 0–1 ie get teh fractional part  of the width
then you find that part of the texture
If the wall is facing left or up, but the player hits it from the
right or below, the visible face should be reversed.
Scale it to the texture width

*/

int get_tex_x(t_ray *ray, t_texture *tex, t_map *map)
{
    double wall_hit_pos; // fractional position along the wall
    int tex_x;
    (void)map;

    if (ray->vertical_hit)
        wall_hit_pos = ray->hit[Y];  // use Y position for vertical walls
    else
        wall_hit_pos = ray->hit[X];  // use X position for horizontal walls

    // Get only the fractional part within the tile
    wall_hit_pos -= floor(wall_hit_pos / TILE_SIZE) * TILE_SIZE;

    // Flip texture horizontally if needed
    if ((ray->vertical_hit && is_ray_facing(WEST, ray->angle)) ||
        (!ray->vertical_hit && is_ray_facing(NORTH, ray->angle)))
    {
        wall_hit_pos = TILE_SIZE - wall_hit_pos;
    }

    
    // Map fractional position to texture X coordinate
    tex_x = (int)((wall_hit_pos / TILE_SIZE) * tex->width);

    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;

    return tex_x;
}

t_render_slice calculate_slice(t_mlx *mlx, t_ray *ray, int col, t_cub_elements *elem)
{
    t_render_slice slice;
    t_map *map = elem->map;
    double corrected_dist;
    double dist_proj_plane;
    double raw_line_h;   /* double, unclamped */
    int draw_line_h;     /* integer, clamped for drawing */
    int start, end;
    t_texture *tex;
    int texx;

    /* 1) guard tiny distances to avoid div-by-zero */
    corrected_dist = (double)ray->distance * cos(ray->angle - elem->player.angle);
    if (corrected_dist <= 0.00001)
        corrected_dist = 0.00001;

    /* 2) projection plane distance (depends on screen width and FOV) */
    dist_proj_plane = ((double)mlx->width / 2.0) / tan(FOV / 2.0);

    /* 3) calculate on-screen wall height (double, do NOT clamp yet) */
    raw_line_h = ((double)TILE_SIZE / corrected_dist) * dist_proj_plane;

    /* integer line height for drawing (clamp to screen) */
    draw_line_h = (int)raw_line_h;
    if (draw_line_h < 1) draw_line_h = 1;
    if (draw_line_h > mlx->height) draw_line_h = mlx->height;

    /* 4) compute top & bottom pixels (centered vertically) */
    start = (mlx->height / 2) - (draw_line_h / 2);
    if (start < 0) start = 0;
    end = start + draw_line_h;
    if (end >= mlx->height) end = mlx->height - 1;

    /* 5) compute texture X coordinate */
    tex = select_texture(elem, ray);
    texx = get_tex_x(ray, tex, map);

    /* 6) fill slice struct */
    slice.x = col;
    slice.texX = texx;
    slice.start = start;
    slice.end = end;
    slice.line_h = draw_line_h;   /* for drawing */
    slice.line_h_d = raw_line_h;  /* original double, for accurate texture mapping */

    return slice;
}


/*
 It accounts for where the wall starts on the screen relative
  to the screen's center and its own height,
  ensuring the texture isn't awkwardly cut off or shifted.
: The modulo operator (%) is used here to handle texture wrapping.
The draw_wall_column fn iterates through each vertical pix that makes up a
single column of a rendered wall segment.
For each screen pixel, it calculates the corresponding Y-coordinat
e on the texture using the step and texPos variables.
This ensures that the texture is scaled and aligned correctly
 as it's drawn vertically on the screen, whether it needs to be compressed,
	stretched, or repeated.
 Finally, it fetches the color from the texture and draws it onto the screen.
*/
void draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice,
                      t_ray *ray, t_cub_elements *elem)
{
    double step;
    double tex_y;
    int y;

    int start = slice->start;
    int end = slice->end;
(void) ray;
    // Clamp to screen bounds
    if (start < 0) start = 0;
    if (end > mlx->height) end = mlx->height;

    // 1) Draw ceiling
    for (y = 0; y < start; y++) {
        put_pixel(slice->x, y, elem->ceiling_color->hex_color, mlx);
    }

    // 2) Prepare texture mapping
    step = (double)tex->height / slice->line_h_d;
    tex_y = (start - (mlx->height / 2) + (slice->line_h_d / 2)) * step;
    if (tex_y < 0) {
        // Debug: clamp negative tex_y
        printf("[DEBUG] Clamping negative tex_y start (%f) to 0\n", tex_y);
        tex_y = 0;
    }

    // 3) Draw wall slice
    for (y = start; y < end; y++)
    {
        int tex_y_int = (int)tex_y;
        if (tex_y_int < 0) tex_y_int = 0;
        if (tex_y_int >= tex->height) tex_y_int = tex->height - 1;

        int color = get_tex_pixel(tex, slice->texX, tex_y_int);

        // Optional: detect suspicious colors (like green tint)
        if ((color & 0x00FF00) > 0x007F00 && (color & 0xFF0000) < 0x003F00) {
            printf("[DEBUG] Possible green pixel at x=%d y=%d, color=0x%X\n", slice->x, y, color);
        }

        put_pixel(slice->x, y, color, mlx);

        tex_y += step;
    }

    // 4) Draw floor
    for (y = end; y < mlx->height; y++) {
        put_pixel(slice->x, y, elem->floor_color->hex_color, mlx);
    }
}

void draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
    for (int x = 0; x < mlx->width; x++)
    {
        t_ray *ray = &rays[x];
        t_render_slice slice = calculate_slice(mlx, ray, x, elem);
        t_texture *tex = select_texture(elem, ray);

        draw_wall_column(mlx, tex, &slice, ray, elem);
    }

    // Push the frame to window
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}