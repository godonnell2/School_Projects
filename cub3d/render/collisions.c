/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:10 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/08 16:38:29 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Calc how far to step for each next horizontal gridline intersection
float	calculate_y_intercept(float angle, t_player *player)
{
	int	tile_y;
	
	tile_y = floor(player->player_y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing(SOUTH, angle))
		return (tile_y - 0.0001f);
	else
		return (tile_y + TILE_SIZE);
}

float	calculate_x_intercept(float angle, t_player *player)
{
	int	tile_x;
	tile_x = floor(player->player_x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing(EAST, angle))
		return (tile_x - 0.0001f);
	else
		return (tile_x + TILE_SIZE);
}

// use dda to move along and check if go outside map or hit wall
// and then record where it is
static void	trace_ray(t_map *map, t_ray_step *step, t_cast *h)
{
	int	m_x;
	int	m_y;

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
			return ;
		}
		if (map->map[m_y][m_x] == '1')
		{
			h->hit[X] = step->next_x;
			h->hit[Y] = step->next_y;
			h->hitted = true;
			h->content = map->map[m_y][m_x];
			return ;
		}
		step->next_x += step->x_step;
		step->next_y += step->y_step;
	}
}

/*
If facing South, you want the gridline below you → add tile_size.
If facing North, you want the gridline above you,
	but if you're exactly on a gridline,
 subtract a tiny amount to avoid peeking into the wrong tile,
	seeing trhough walls.
 facing south floor(120.5 / 64) = floor(1.8828) = 1
1 * 64 = 64
64 + 64 = 128
facing north	floor(120.5 / 64) = 1
1 * 64 = 64
64 + 64 = 128
  // Calc  x at the intercept
tan(angle) = opposite / adjacent = (Δy) / (Δx)
find angle
find starting pt intercept
then calc how far to go!!! the y is always easy tile size
trigonometry for x
*/

void	find_horizontal_collision(t_map *map, float angle, t_cast *h, t_player *player)
{
	float		y_step;
	float		x_step;
	t_ray_step	step;
	t_direction	vertical_dir;

	if (is_ray_facing(NORTH, angle))
		vertical_dir = NORTH;
	else
		vertical_dir = SOUTH;
	if (vertical_dir == SOUTH)
	{
		y_step = TILE_SIZE;
		x_step = TILE_SIZE / tan(angle);
	}
	else
	{
		y_step = -TILE_SIZE;
		x_step = -TILE_SIZE / tan(angle);
	}
	step = init_ray_step(player->player_x + (calculate_y_intercept(angle, player)
				- map->player_y) / tan(angle), calculate_y_intercept(angle, player), x_step, y_step);
	step.vertical_dir = vertical_dir;
	trace_ray(map, &step, h);
}

void	find_vertical_collision(t_map *map, float angle, t_cast *v, t_player *player)
{
	float		x_step;
	float		y_step;
	t_ray_step	step;
	t_direction	horizontal_dir;

	if (is_ray_facing(WEST, angle))
		horizontal_dir = WEST;
	else
		horizontal_dir = EAST;
	if (horizontal_dir == EAST)
	{
		x_step = TILE_SIZE;
		y_step = TILE_SIZE * tan(angle);
	}
	else
	{
		x_step = -TILE_SIZE;
		y_step = -TILE_SIZE * tan(angle);
	}
	step = init_ray_step(calculate_x_intercept( angle, player), player->player_y
			+ (calculate_x_intercept( angle, player) - player->player_x) * tan(angle),
			x_step, y_step);
	step.horizontal_dir = horizontal_dir;
	trace_ray(map, &step, v);
}
