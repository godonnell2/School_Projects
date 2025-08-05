/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/05 18:12:17 by gro-donn         ###   ########.fr       */
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
void store_ray_data(t_ray *ray, t_cast *cast, float angle, bool vertical)
{
    ray->angle = angle;
    ray->dist = cast->distance;
    ray->hit[X] = cast->hit[X];
    ray->hit[Y] = cast->hit[Y];
    ray->vertical_hit = vertical;
    
    // Determine wall orientation
    if (vertical) {
        ray->wall_content = is_ray_facing(EAST, angle) ? 'E' : 'W';
    } else {
        ray->wall_content = is_ray_facing(NORTH, angle) ? 'N' : 'S';
    }
}

void cast_ray(t_cub_elements *app, float angle, int col, t_ray *rays)
{
    t_cast h, v;
    float fish_eye = cos(app->player.angle - angle);
    
    find_horizontal_collision(app->map, angle, &h);
    find_vertical_collision(app->map, angle, &v);
    
    if (!h.hitted) h.distance = INFINITY;
    else h.distance = hit_distance(app->map->player_x, app->map->player_y,
                                   h.hit[X], h.hit[Y]) * fish_eye;
    
    if (!v.hitted) v.distance = INFINITY;
    else v.distance = hit_distance(app->map->player_x, app->map->player_y,
                                   v.hit[X], v.hit[Y]) * fish_eye;
    
    if (h.distance < v.distance)
        store_ray_data(&rays[col], &h, angle, false);
    else
        store_ray_data(&rays[col], &v, angle, true);
}

void raycasting(t_data *app, t_ray *rays, t_cub_elements *elem)
{
    float ray_angle = elem->player.angle - HALF_FOV;
    float ray_step = FOV / app->mlx->width;
    
    for (int col = 0; col < app->mlx->width; col++) {
        ray_angle = normalize_angle(ray_angle);
        cast_ray(elem, ray_angle, col, rays);
        ray_angle += ray_step;
    }
}