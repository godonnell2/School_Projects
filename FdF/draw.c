/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:23:50 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 19:14:02 by gro-donn         ###   ########.fr       */
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

static void	update_bresenham(t_bresenham *vars, t_line *line)
{
	if (vars->e2 > -vars->dy)
	{
		vars->err -= vars->dy;
		line->x0 += vars->sx;
	}
	if (vars->e2 < vars->dx)
	{
		vars->err += vars->dx;
		line->y0 += vars->sy;
	}
}

void	draw_line(t_data *t_data_pix, t_line *line)
{
	t_bresenham	vars;

	vars.dx = abs(line->x1 - line->x0);
	vars.dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		vars.sx = 1;
	else
		vars.sx = -1;
	if (line->y0 < line->y1)
		vars.sy = 1;
	else
		vars.sy = -1;
	vars.err = vars.dx - vars.dy;
	while (1)
	{
		put_pixel(t_data_pix, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		vars.e2 = vars.err * 2;
		update_bresenham(&vars, line);
	}
}
