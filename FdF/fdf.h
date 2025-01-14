#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h> //minilbx fns
# define STDERR 2
typedef struct s_map
{
    int width;        // Number of columns in the map
    int height;       // Number of rows in the map
    int ***array;     // 3D array to hold the map data (z values)
    int z_min;        
    int z_max;       
} t_map;

typedef struct s_mlx_context 
{
   void	* mlx;
    void * mlx_win;
} t_mlx_context;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
int handle_keypress(int keycode, void *param);
int handle_exit(void *param);
#endif