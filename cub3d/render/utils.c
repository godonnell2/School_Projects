/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:23:19 by gro-donn          #+#    #+#             */
/*   Updated: 2025/07/19 13:26:52 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// floating pt remainder ie keep between 0 and 2pi for our calcs
// keep remainder of angle / 2pi
float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

// Purpose: Euclidean distance from player to wall hit.
// ie shortest dir distance from pythagorean theorm
float	hit_distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_ray_step	init_ray_step(float x_intercept, float y_intercept, float x_step,
		float y_step)
{
	t_ray_step	step;

	step.next_x = x_intercept;
	step.next_y = y_intercept;
	step.x_step = x_step;
	step.y_step = y_step;
	return (step);
}

t_render_slice	init_render_slice(int x, int texX, int start_end[2], int line_h)
{
	t_render_slice	slice;

	slice.x = x;
	slice.texX = texX;
	slice.start = start_end[0];
	slice.end = start_end[1];
	slice.line_h = line_h;
	return (slice);
}
