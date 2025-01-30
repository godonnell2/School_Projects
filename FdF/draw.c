/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:23:50 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/30 21:30:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	put_pixel(t_data *t_data_pix, int x, int y, int color)
{
	char	*dst;

	dst = t_data_pix->addr + (y * t_data_pix->line_length + x
			* (t_data_pix->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	update_bresenham(t_bresenham *vars, t_point2d *start)
{
	if (vars->e2 > -vars->dy)
	{
		vars->err -= vars->dy;
		start->x += vars->sx;
	}
	if (vars->e2 < vars->dx)
	{
		vars->err += vars->dx;
		start->y += vars->sy;
	}
}

void	draw_line(t_data *t_data_pix, t_point2d start, t_point2d end, int color)
{
	t_bresenham	vars;

	vars.dx = abs((int)end.x - (int)start.x);
	vars.dy = abs((int)end.y - (int)start.y);
	if (start.x < end.x)
		vars.sx = 1;
	else
		vars.sx = -1;
	if (start.y < end.y)
		vars.sy = 1;
	else
		vars.sy = -1;
	vars.err = vars.dx - vars.dy;
	while (1)
	{
		put_pixel(t_data_pix, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		vars.e2 = vars.err * 2;
		update_bresenham(&vars, &start);
	}
}
