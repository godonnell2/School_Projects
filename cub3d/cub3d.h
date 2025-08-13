/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:20 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/13 10:01:03 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "mlx.h"

// maths defines
#define PI 3.14159265
#define TWO_PI 6.28318530
#define HALF_PI 1.57079632


#define FOV (M_PI / 3) // 60 degrees in radians
#define HALF_FOV (FOV / 2)

#define MOVE_SPEED 1.0f   // Speed of forward/backward/strafe
#define ROTATE_SPEED 0.05f // Radians per frame (~3 degrees)


# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KeyPress 2
# define KeyRelease 3
# define DestroyNotify 17
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define NoEventMask 0

#define COLLISION_PADDING 5.0

#define WIDTH 640 //we are defining a viewport to play the game so it ok to hardcode this 
#define HEIGHT 480

#define TILE_SIZE 64


typedef struct s_map
{
    char **map;
    int width;
    int height;
  int player_x; 
   int player_y;
    int tile_size;
} t_map;

typedef struct s_texture
{
    void    *img_ptr;        // mlx image pointer
    char    *data;           // pixel buffer (same as data_addr)
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    char    *path;           // optional, for debug or filepath
}   t_texture;
typedef struct s_color
{
    int rgb_color[3];
    bool color_set;
    int hex_color;
} t_color;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;  // screen w
    int height; // screen h
    int color;  // column color
} t_mlx;

typedef struct s_keys {
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_player
{
float player_x;
float player_y;
    float dir_x;    // dir vect X
    float dir_y;    // dir vec Y
    float plane_x;  // cam plane X
    float plane_y;  // cam plane Y
    float angle;    // curr facing angle (optional)
    float ray_step; // horizontal FOV step per column
} t_player;
//  float   x;           changed refs to his struct cub_elements->map->player_x
// float   y;           // changes refs to his in another struct
typedef struct s_cub_elements
{
    t_texture *no_text;
    t_texture *so_text;
    t_texture *we_text;
    t_texture *ea_text;
    t_color *floor_color;
    t_color *ceiling_color;
    t_map *map;
    t_player player;
    t_texture texture;
} t_cub_elements;

typedef struct s_data
{
    t_mlx *mlx;
    t_cub_elements *elem;
    t_keys	keys;
} t_data;
typedef enum e_direction
{
    EAST,
    NORTH,
    WEST,
    SOUTH
} t_direction;

enum
{
    X,
    Y
};

typedef struct s_cast
{
    bool hitted;
    float hit[2];   // exact X,Y hit point
    float distance; // perp-corrected distance
    char content;   // map cell content ('1' for wall)
} t_cast;

typedef struct s_ray
{
    float distance;       // raw distance from player
    float correct_dist;   // distance corrected for fish-eye
    float angle;          // ray angle
    double hit[2];        // exact hit coords
    bool N;
    bool E;
    bool vertical_hit;    // did we hit a vertical wall?
    char wall_content;    // which wall texture to use ('N','S','E','W')
    int wall_top;         // pixel y for top of wall
    int wall_bottom;      // pixel y for bottom of wall
} t_ray;

typedef struct s_ray_step
{
    float next_x;
    float next_y;
    float x_step;
    float y_step;
    t_direction vertical_dir;
    t_direction horizontal_dir;
} t_ray_step;

typedef struct s_render_slice
{
    int x;
    int texX;
    int start;
    int end;
    int     line_h;    // clamped integer height (for drawing)
    double  line_h_d;  // original projected height (double) — for texture mapping
} t_render_slice;

typedef struct s_slice
{
    int top_pixel;
    int bottom_pixel;
    int height;
}   t_slice;



void check_arguments(int argc, char **argv);
int ft_strcmp(const char *s1, const char *s2);
bool scan_cub_elements(const char *filename,
                       t_cub_elements *cub3d, t_color *ceil, t_color *floor);
bool assign_color(char *id, char *val, t_cub_elements *cub3d);
bool is_map_line(char *line);
bool close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu);
void free_cub_elements(t_cub_elements *cub3d, void *mlx_ptr);
char *trim_spaces(char *str);
bool map_parsing(const char *filename, t_cub_elements *cub3d);
t_map *init_map(void);
char **copy_map(char **map, int height);
void free_map(t_map *map);
void free_texture(t_texture *texture, void *mlx_ptr);
int init_mlx(t_mlx *mlx);
bool cub3d_parsing(int argc, char **argv, t_cub_elements *cub3d);
bool validate_map(t_cub_elements *cub3d);
int xpm_to_img(t_cub_elements *elem, t_mlx *mlx);
int data_init(int argc, char **argv, t_data *data);
void free_array(char **array);
bool check_color_id(char *id, t_cub_elements *cub3d);
char *join_strings(char **strings);
void free_all(t_data *data);

// render
// render.c
int	handle_keyrelease(int keycode, t_data *data);
int	handle_keypress(int keycode, t_data *data);
void render_frame(t_data *app);
void move_player(t_map *map, t_player *player, t_keys keys);
void	handle_movement(t_data *data);

// putline.c
void	fill_floor(t_mlx *mlx, t_cub_elements *elem, int x, int start);
void	fill_ceiling(t_mlx *mlx, t_cub_elements *elem, int x, int start);
void put_pixel(int x, int y, int color, t_mlx *mlx);
//void fill_column(t_mlx *mlx, int x, int y_start, int y_end, int color);
//int rgb_to_hex(int rgb[3]);
t_texture	*select_texture(t_cub_elements *app, t_ray *ray);

// collisions_hor.c
void	find_horizontal_collision(t_map *map, float angle, t_cast *h, t_player *player);
t_ray_step init_ray_step(float x_intercept, float y_intercept, float x_step,
                         float y_step);
                         float	calculate_intercept(float angle, t_player *player, bool is_vertical);
void	find_vertical_collision(t_map *map, float angle, t_cast *v, t_player *player);
int	get_map_y(t_ray_step *step);

// draw_walls.c
void draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem);

// raycasting.c
void raycasting(t_data *app, t_ray *rays, t_cub_elements *elem);

// raycasting utils
bool is_ray_facing(int dir, float angle);
t_ray_step	init_horizontal_step(t_player *player, float angle);
t_ray_step	init_vertical_step(t_player *player, float angle);

// utils.c
float hit_distance(float x1, float y1, float x2, float y2);
float normalize_angle(float angle);
t_ray_step init_ray_step(float x_intercept, float y_intercept, float x_step,
                         float y_step);
t_render_slice init_render_slice(int x, int texX, int start_end[2], int line_h, double line_h_d);
float get_padding(float move); 
bool is_wall(t_map *map, float x, float y); 

int get_tex_pixel(t_texture *tex, int x, int y);

 int	handle_close(t_data *data);

 

//movement.c
bool	is_wall(t_map *map, float x, float y);
void	move_forward(t_map *map, t_player *player, float speed);
void	move_backward(t_map *map, t_player *player, float speed);
void	move_left(t_map *map, t_player *player, float speed);
void	rotate_left(t_player *player, float angle);
void	rotate_right(t_player *player, float angle);
void	move_right(t_map *map, t_player *player, float speed);
#endif