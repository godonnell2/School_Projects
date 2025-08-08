/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/08 17:06:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Copies data from prev col if two distances tie ie same distanc */
// static void	copy_last_ray(t_ray *rays, int col)
// {
// 	t_ray	*curr;
// 	t_ray	*prev;

// 	curr = &rays[col];
// 	prev = &rays[col - 1];
// 	*curr = *prev;
// }

/*
The corrected distance to the wall
The exact hit coordinates
What type of wall you hit (e.g., '1' or texture ID)
*/

void	store_ray_data(t_ray *ray, t_cast *cast, float angle, bool vertical)
{
	ray->angle = angle;
	ray->distance = cast->distance;
	ray->hit[X] = cast->hit[X];
	ray->hit[Y] = cast->hit[Y];
	ray->wall_content = cast->content;
	ray->vertical_hit = vertical;

}

/*
 Fires one ray at a given angle from the player's position.
 fish-eye correction to keep walls from looking warped.
collission returns where the ray first hits a wall horizontally
and then verticaly
these fill out t_cast structs
Rays farther from the center of the screen travel at an angle —
without correction, those walls look stretched.
cos(...) scales the distance to correct that —
this way, walls appear vertically aligned even if the ray is at an angle.
no hit infinity otelse we calc  distance between player
n hit point Pythag

 corrected for fish-eye.
Store the result into the ray buffer (rays[col])
so rendering code knows what to draw.
 one ray result per screen column.
The vertical_hit flag is important for later:
Shade vertical walls darker Pick the right tex(e.g., N wall vs E wall)
 */

static void cast_ray(t_cub_elements *elem, float angle, int col, t_ray *rays)
{
    t_cast  h;
    t_cast  v;
    float   px = elem->player.player_x;
    float   py = elem->player.player_y;

    find_horizontal_collision(elem->map, angle, &h, &elem->player);
    find_vertical_collision(elem->map, angle, &v, &elem->player);

    // Use raw distances for comparison
    if (!h.hitted)
        h.distance = INFINITY;
    else
        h.distance = hit_distance(px, py, h.hit[X], h.hit[Y]);

    if (!v.hitted)
        v.distance = INFINITY;
    else
        v.distance = hit_distance(px, py, v.hit[X], v.hit[Y]);

    // Pick closer ray (before fisheye correction)
    if (h.distance < v.distance)
    {
        h.distance *= cos(elem->player.angle - angle); // fisheye correction here
        store_ray_data(&rays[col], &h, angle, /*vertical_hit=*/false);
    }
    else
    {
        v.distance *= cos(elem->player.angle - angle); // fisheye correction here
        store_ray_data(&rays[col], &v, angle, /*vertical_hit=*/true);
    }
}
/* Cast a ray for each column across the screen
If their FOV is 60 degrees, then:

They can see 30 degrees to the left

And 30 degrees to the right of A
angle = π/2 - π/6 = π/3      // left-most ray
			↑
			|
		/
		/     ← rays go from here ...
		/
		•────────→ π/2 ← straight ahead
		\
		\     ← ... to here
		\
			↓
		π/2 + π/6 = 2π/3        // right-most ray

ach ray_step moves you a tiny bit to the right,
	until you sweep from left to right across the whole FOV.


*/
void raycasting(t_data *app, t_ray *rays, t_cub_elements *elem)
{
    float angle;
    int col;
    float ray_step;

    ray_step = FOV / (float)app->mlx->width;  // Use app->mlx->width, not WIDTH unless WIDTH is defined
    angle = elem->player.angle - HALF_FOV;
    col = 0;
    while (col < app->mlx->width)
    {
        angle = normalize_angle(angle);
        cast_ray(elem, angle, col, rays);
        angle += ray_step;  // Use local variable here
        col++;
    }


}
