/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:23:50 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 16:42:46 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>

static void put_pixel(t_data *t_data_pix, int x, int y, int color)
{
	char *dst;
 int window_width = 1100;
	int window_height = 800;
	if (x < 0 || x >= window_width  || y < 0 || y >= window_height)
    {
       
        return; // Skip putting the pixel if out of bounds THIS IS HARDCODE NEEED TO FIX SO WINDOW HEIGHT AND WIDE CENTRALISED
    }

	dst = t_data_pix->addr + (y * t_data_pix->line_length + x * (t_data_pix->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void update_bresenham(t_bresenham *vars, t_line *line)
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

void draw_line(t_data *t_data_pix, t_line *line)
{
	t_bresenham vars;

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
			break;
		vars.e2 = vars.err * 2;
		update_bresenham(&vars, line);
	}
}
