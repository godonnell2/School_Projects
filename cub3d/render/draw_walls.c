/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/08 17:24:09 by gro-donn         ###   ########.fr       */
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
    double wallx;
    (void) map;
    if (ray->vertical_hit)
        wallx = ray->hit[Y];
    else
        wallx = ray->hit[X];

    // fractional part inside the tile
    wallx = fmod(wallx, TILE_SIZE);
    if (wallx < 0)
        wallx += TILE_SIZE;  // handle negative fmod

    double tex_pos = wallx / TILE_SIZE;  // normalize [0,1)

    int texx = (int)(tex_pos * tex->width);

    // Flip texture coordinate based on ray direction
    if ((ray->vertical_hit && ray->angle < M_PI) ||
        (!ray->vertical_hit && ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2))
    {
        texx = tex->width - texx - 1;
    }

    // Clamp to texture boundaries
    if (texx < 0)
        texx = 0;
    if (texx >= tex->width)
        texx = tex->width - 1;

   // printf("get_tex_x: hit=(%.2f, %.2f), wallx=%.2f, texx=%d\n",
     //      ray->hit[X], ray->hit[Y], wallx, texx);

    return texx;
}
t_render_slice calculate_slice(t_mlx *mlx, t_ray *ray, int col, t_cub_elements *elem)
{
    t_render_slice slice;
    t_map *map = elem->map;
    double corrected_dist;
    double dist_proj_plane;
    int line_h;
    int start;
    int end;
    t_texture *tex;
    int texx;

    /* 1) guard tiny distances to avoid div-by-zero */
    corrected_dist = (double)ray->distance * cos(ray->angle - elem->player.angle);
    if (corrected_dist <= 0.00001)
        corrected_dist = 0.00001;

    /* 2) projection plane distance (depends on screen width and FOV) */
    dist_proj_plane = ((double)mlx->width / 2.0) / tan(FOV / 2.0);

    /* 3) calculate on-screen wall height (uses map->tile_size) */
    line_h = (int)(( (double)TILE_SIZE / corrected_dist ) * dist_proj_plane);

    /* clamp */
    if (line_h < 1) line_h = 1;
    if (line_h > mlx->height) line_h = mlx->height;

    /* 4) compute top & bottom pixels (centered vertically) */
    start = (mlx->height / 2) - (line_h / 2);
    if (start < 0) start = 0;
    end = start + line_h;
    if (end >= mlx->height) end = mlx->height - 1;

    /* 5) compute texture X coordinate using existing helper */
    tex = select_texture(elem, ray);               // uses elem & ray to pick N/S/E/W
    texx = get_tex_x(ray, tex, map);

    /* 6) fill slice struct */
    slice.x = col;
    slice.texX = texx;
    slice.start = start;
    slice.end = end;
    slice.line_h = line_h;

    /* optional debug prints (first few columns only) */
    if (col < 8) {
        printf("Raw dist: %.2f, Corrected dist: %.2f, line_h: %d\n", ray->distance, corrected_dist, line_h);
    }

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
void	draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice)
{
	double	step;
	double	texpos;
	int		y;
	int		color;

	step = (double)tex->height / slice->line_h;
	 // Start texpos so that the top of the wall slice maps to the top of the texture
	 // nsures the texture is always vertically centered and mapped correctly to the wall slice.
	texpos = (slice->start - (mlx->height / 2 - slice->line_h / 2)) * step;
	y = slice->start;
	while (y < slice->end)
	{
		int texy = (int)texpos;
        if (texy < 0) texy = 0;
        if (texy >= tex->height) texy = tex->height - 1;
		texpos += step;
		
		color = get_tex_pixel(tex, slice->texX, texy);
		put_pixel(slice->x, y, color, mlx);
		y++;
	}
}

void draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
    // 1. Draw ceiling and floor background
    for (int y = 0; y < mlx->height; y++)
    {
        int color = (y < mlx->height / 2)
            ? elem->ceiling_color->hex_color
            : elem->floor_color->hex_color;

        for (int x = 0; x < mlx->width; x++)
            put_pixel(x, y, color, mlx);
    }

    // 2. Draw walls column by column
    for (int x = 0; x < mlx->width; x++)
    {
        t_ray *ray = &rays[x];

        // Calculate wall slice dimensions
        t_render_slice slice = calculate_slice(mlx, ray, x, elem);

        // Pick correct texture (N/S/E/W)
        t_texture *tex = select_texture(elem, ray);

        // Draw vertical wall strip with texture mapping
        draw_wall_column(mlx, tex, &slice);
    }

    // 3. Push frame to window
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}