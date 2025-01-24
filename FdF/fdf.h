#ifndef FDF_H
#define FDF_H

#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h> //minilbx fns
#define STDERR 2
#define SCALE_FACTOR 30
typedef struct s_map
{
    int cols;     
    int rows;     
    int ***array; // 3D array to hold the map data (z values)
    long z_min;
    long z_max;
} t_map;

typedef struct s_point3d
{
    float x;
    float y;
    float z;
} t_point3d;
typedef struct s_mlx_context
{
    void *mlx;
    void *mlx_win;
} t_mlx_context;

typedef struct s_point2d
{
    float x;
    float y;
} t_point2d;

typedef struct s_edge
{
    int start;
    int end;
} t_edge;
typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

int handle_keypress(int keycode, void *param);
int handle_exit(void *param);

char *read_file_to_buffer(const char *filename);
void determine_dimensions(const char *buffer, t_map *map);

void find_min_max(long *array, int array_size, t_map *map);
long *read_map_into_array(t_map *map, char *buffer);
void print_map_array(t_map *map);
void populate_edges(t_map *map, t_edge **edges, int *edges_count);

void generate_3d_points(t_map *map, long *map_array, t_point3d *points);
void convert_to_isometric(t_map *map, t_point3d *points, t_point2d *iso_points);
void scale_and_offset_points(t_point2d *iso_points, t_map *map, int window_width, int window_height);
#endif