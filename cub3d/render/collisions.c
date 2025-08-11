/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:10 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/11 16:04:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float calculate_intercept(float angle, t_player *player, bool is_vertical)
{
    if (is_vertical)
    {
        int tile_x = floor(player->player_x / TILE_SIZE) * TILE_SIZE;
        if (is_ray_facing(EAST, angle))
            return tile_x + TILE_SIZE;
        else
            return tile_x - 0.0001f;
    }
    else
    {
        int tile_y = floor(player->player_y / TILE_SIZE) * TILE_SIZE;
        if (is_ray_facing(SOUTH, angle))
            return tile_y + TILE_SIZE;
        else
            return tile_y - 0.0001f;
    }
}
// Adjust y coordinate for horizontal rays to check correct tile based on ray direction
static void trace_ray(t_map *map, t_ray_step *step, t_cast *h)
{
    int m_x, m_y;

    while (1)
    {
        m_x = (int)(step->next_x) / TILE_SIZE;

        
        if (step->vertical_dir == NORTH)
            m_y = ((int)(step->next_y) - 1) / TILE_SIZE;
        else
            m_y = (int)(step->next_y) / TILE_SIZE;

        if (m_x < 0 || m_x >= map->width || m_y < 0 || m_y >= map->height)
        {
            h->hitted = false;
            return;
        }

        if (map->map[m_y][m_x] == '1')  
        {
            h->hit[X] = step->next_x;
            h->hit[Y] = step->next_y;
            h->hitted = true;
            h->content = map->map[m_y][m_x];
            return;
        }

        step->next_x += step->x_step;
        step->next_y += step->y_step;
    }
}

   // x step is delta x per y step: x_step = TILE_SIZE / tan(angle)
   // Protect against tan(angle) = 0 or infinite
    // If ray facing west, x_step should be negative
	    // Calculate initial x intercept for horizontal line
void find_horizontal_collision(t_map *map, float angle, t_cast *h, t_player *player)
{
    float y_intercept = calculate_intercept(angle, player, false); 
    float x_intercept;
    float y_step;
    float x_step;

    float tan_angle = tan(angle);
    if (fabs(tan_angle) < 0.0001f)
        tan_angle = 0.0001f;

    y_step = is_ray_facing(SOUTH, angle) ? TILE_SIZE : -TILE_SIZE;
    x_step = TILE_SIZE / tan_angle;

    if ((x_step > 0 && is_ray_facing(WEST, angle)) || (x_step < 0 && is_ray_facing(EAST, angle)))
        x_step = -x_step;

    x_intercept = player->player_x + (y_intercept - player->player_y) / tan_angle;

    t_ray_step step = init_ray_step(x_intercept, y_intercept, x_step, y_step);
    step.vertical_dir = is_ray_facing(SOUTH, angle) ? SOUTH : NORTH;

    trace_ray(map, &step, h);
}
//  // y_step is delta y per x step: y_step = TILE_SIZE * tan(angle)
//      // Fix sign if direction opposite
void find_vertical_collision(t_map *map, float angle, t_cast *v, t_player *player)
{
    float x_intercept = calculate_intercept(angle, player, true);
    float y_intercept;
    float x_step;
    float y_step;

    float tan_angle = tan(angle);
    if (fabs(tan_angle) < 0.0001f)
        tan_angle = 0.0001f;

    x_step = is_ray_facing(EAST, angle) ? TILE_SIZE : -TILE_SIZE;
    y_step = TILE_SIZE * tan_angle;

    if ((y_step > 0 && is_ray_facing(NORTH, angle)) || (y_step < 0 && is_ray_facing(SOUTH, angle)))
        y_step = -y_step;

    y_intercept = player->player_y + (x_intercept - player->player_x) * tan_angle;

    t_ray_step step = init_ray_step(x_intercept, y_intercept, x_step, y_step);
    step.vertical_dir = is_ray_facing(EAST, angle) ? EAST : WEST;

    trace_ray(map, &step, v);
}

