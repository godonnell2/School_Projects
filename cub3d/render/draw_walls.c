/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/07/30 09:55:20 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Draws vertical wall slices based on distances in `rays[]`
vertical_hit = wall is vertical, facing east/west

+----+     ← wall aligned vertically
|    | ← You hit this wall from the left (so it's EAST-facing)
| P→ | ← vertical hit, wall_content = 'E'
|    |
+----+
horizontal_hit = wall is horizontal, facing north/south
Top-down view of player hitting a horizontal wall:

+----+----+----+
|    |    |    |
+----+----+----+
|    | P  |    |
+----+----+----+
		↑
		ray hit the wall above — a NORTH-facing wall
*/

t_texture	*select_texture(t_cub_elements *app, t_ray *ray)
{
	
	if (ray->vertical_hit)
	{
		if (ray->wall_content == 'E')
			return (app->ea_text);
		else
			return (app->we_text);
	}
	else
	{
		if (ray->wall_content == 'N')
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
Scale it to the texture width
right or below, the visible face should be reversed.
*/
int	get_tex_x(t_ray *ray, t_texture *tex, t_map *map)
{
	double	wallx;
	int		texx;

	if (ray->vertical_hit)
		wallx = map->player_y + ray->dist * sin(ray->angle);
	else
		wallx = map->player_x + ray->dist * cos(ray->angle);
	wallx -= floor(wallx);
	texx = (int)(wallx * tex->width);
	if ((ray->vertical_hit && ray->angle < M_PI) || (!ray->vertical_hit
			&& ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2))
		texx = tex->width - texx - 1;
	return (texx);
}

/*
 Imagine your texture is like a vertical strip.
 You want to make sure that the middle of your texture aligns
 with the middle of the drawn wall column on the screen,
 and the top of the texture aligns with the top of the wall column.
 This calculation sets the initial texPos so that when you iterate
 through y (screen pixels), texY (texture pixels) maps correctly.
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
	int		texy;
	int		color;

	step = (double)tex->height / slice->line_h;
	texpos = (slice->start - mlx->height / 2 + slice->line_h / 2) * step;
	y = slice->start;
	while (y < slice->end)
	{
		texy = (int)texpos % tex->height;
		texpos += step;
		color = get_tex_pixel(tex, slice->texX, texy);
		put_pixel(slice->x, y, color, mlx);
		y++;
	}
}

t_render_slice	calculate_slice(t_mlx *mlx, t_ray *ray, int x,
		t_cub_elements *elem)
{
	t_texture		*tex;
	t_render_slice	slice;
	int				start_end[2];
	int				line_h;
	int				texx;

	line_h = mlx->height / ray->dist;
	start_end[0] = -line_h / 2 + mlx->height / 2;
	if (start_end[0] < 0)
		start_end[0] = 0;
	start_end[1] = line_h / 2 + mlx->height / 2;
	if (start_end[1] >= mlx->height)
		start_end[1] = mlx->height - 1;
	tex = select_texture(elem, ray);
	texx = get_tex_x(ray, tex, elem->map);
	slice = init_render_slice(x, texx, start_end, line_h);
	return (slice);
}

void	draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
	t_render_slice	slice;
	t_texture		*tex;
	t_ray			*ray;
	int				x;

	x = 0;
	while (x < mlx->width)
	{
		ray = &rays[x];
		slice = calculate_slice(mlx, ray, x, elem);
		tex = select_texture(elem, ray);
		fill_column(mlx, x, 0, slice.start);
		draw_wall_column(mlx, tex, &slice);
		fill_column(mlx, x, slice.end, mlx->height);
		x++;
	}
	if (!mlx->img_ptr)//!mlx->mlx_ptr || !mlx->win_ptr)|| 
	{
    	exit(1);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
