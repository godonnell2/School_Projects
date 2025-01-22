/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:26:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/22 20:37:35 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "fdf.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// bresenhams line algorithm
void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, color); 

		if (x0 == x1 && y0 == y1) 
			break;

		int e2 = err * 2;

		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}


//Specialised event handlers
int	main(void)
{
	t_data	img;
	t_mlx_context ctx;
	
	char * buffer = read_file_to_buffer("test_maps/basictest.fdf");

	t_map map;
	determine_dimensions(buffer, &map);

	 long *map_array = read_map_into_array(&map, buffer);
	  int array_size = map.height * map.width;
	 find_min_max(map_array, array_size, &map);
	// int i = 0;
	
	// printf("map.width:%i\n", map.width);
// while(i < array_size)
// {
//         printf("%ld, ", map_array[i]);
// 		i++;
// 		if(i% map.width == 0 )
// 		{
// 			//printf("each line:%i\n", map.width);
// 			 printf("\n");
// 		}
// }
	//printf("%ld, %ld", map.z_min, map.z_max);
	 t_point3d *points = malloc(map.height * map.width * sizeof(t_point3d));
	 generate_3d_points(&map, map_array, points);

    // Print the generated 3D points
    // for (int i = 0; i < map.height * map.width; i++) {
    //     printf("Point %d: (x: %f, y: %f, z: %f)\n", i, points[i].x, points[i].y, points[i].z);
    // }

	

	
	t_point2d *iso_points = malloc(map.height * map.width * sizeof(t_point2d));
	    convert_to_isometric(&map, points, iso_points);
	t_point2d *iso_points = malloc(map.height * map.width * sizeof(t_point2d));
	free(points); 
	free(iso_points);
	exit(1);
	

	ctx.mlx = mlx_init();
	ctx.mlx_win = mlx_new_window(ctx.mlx, 500, 350, "Hello world!");
	img.img = mlx_new_image(ctx.mlx, 500, 350);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
								
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	draw_line(&img, 10, 220, 10, 320, 0x00FF0000);
	draw_line(&img, 10, 220, 100, 20, 0x00FF0000);
	draw_line(&img, 100, 20, 10, 320, 0x00FF0000);
	mlx_put_image_to_window(ctx.mlx, ctx.mlx_win, img.img, 0, 0);
	
	
    mlx_hook(ctx.mlx_win, 17, 0, handle_exit, &ctx);      
    mlx_key_hook(ctx.mlx_win, handle_keypress, &ctx);   
	
	// NEED TO BE AT END!!!
	mlx_loop(ctx.mlx);
}
//17 = DestroyNotify    NAME OF LIB used by minilibx for linux = x11 x.h    
//OS has told x that the window close button has been pressed  
// 0 is the mask it says no mask! look at ALL bits
// (otherwise can bit shift for more specificity)
//a triangle is a shape where three lines connect  
//2 lines meet at each point 

/*
Isometric Projection Formula
In isometric projection:

Orthographic: No perspective or distortion; parallel lines remain parallel.
 Views the object straight-on from one axis (e.g., top, front, side).
 No foreshortening unless explicitly specified for oblique views.
 Isometric: Maintains proportions without depth distortion, using equal angles
 between axes. 
 Rotates the object so that all three axes (X, Y, Z) are equally foreshortened. 
 The angle between axes in 2D is 120
 Shows a pseudo-3D view where all three dimensions are visible.
 Applies equal foreshortening along all three axes.
 .
Perspective: Includes depth distortion to simulate the human eye.




*/