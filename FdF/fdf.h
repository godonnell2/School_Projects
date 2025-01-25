/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:58:11 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/25 07:48:03 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h> //minilbx fns
# include <stdlib.h>
# define STDERR 2
# define SCALE_FACTOR 30

typedef struct s_data_pix
{
	char	*addr;
	int		line_length;
	int		bits_per_pixel;
} t_data_pix;

typedef struct s_line
{
	int x0;
	int y0;
	int x1;
	int y1;
	int color;
} t_line;

typedef struct s_bresenham
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
} t_bresenham;
typedef struct s_map
{
	int		cols;
	int		rows;
	int ***array; // 3D array to hold the map data (z values)
	long	z_min;
	long	z_max;
}			t_map;

typedef struct s_point3d
{
	float	x;
	float	y;
	float	z;
}			t_point3d;
typedef struct s_mlx_context
{
	void	*mlx;
	void	*mlx_win;
}			t_mlx_context;

typedef struct s_point2d
{
	float	x;
	float	y;
}			t_point2d;

typedef struct s_edge
{
	int		start;
	int		end;
}			t_edge;
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

int			handle_keypress(int keycode, void *param);
int			handle_exit(void *param);

void	ft_printf(const char *mandatory_string, ...);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
void	ft_printchar(char c, int fd);

char *read_file_to_buffer(const char *filename);
void	handle_error(const char *message);
void		determine_dimensions(const char *buffer, t_map *map);

long		*read_map_into_array(t_map *map, char *buffer);
void		print_map_array(t_map *map);
void	generate_horizontal_edges(t_map *map, t_edge *edges, int *edge_index);
void	generate_vertical_edges(t_map *map, t_edge *edges, int *edge_index);
void	populate_edges(t_map *map, t_edge **edges, int *edges_count);

void		find_min_max(long *array, int array_size, t_map *map);
void		generate_3d_points(t_map *map, long *map_array, t_point3d *points);
void		convert_to_isometric(t_map *map, t_point3d *points,
				t_point2d *iso_points);
void		scale_and_offset_points(t_point2d *iso_points, t_map *map,
				int window_width, int window_height);

void	draw_line(t_data *data, t_line *line);
#endif