/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:23:33 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/09 15:17:12 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// basically each quater circle is pi/2 the one on the right is 0 or 2pi
// defining dir of ray
bool is_ray_facing(int dir, float angle)
{
    angle = normalize_angle(angle);

    bool result = false;

    if (dir == NORTH)
        result = (angle > PI && angle < TWO_PI);
    else if (dir == SOUTH)
        result = !is_ray_facing(NORTH, angle);
    else if (dir == WEST)
        result = (angle > HALF_PI && angle < 1.5 * PI);
    else if (dir == EAST)
        result = !is_ray_facing(WEST, angle);

    return result;
}