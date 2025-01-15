#include "fdf.h"
#include <stdio.h>

int handle_exit(void *param)
{
	printf("exiting\n");
    t_mlx_context *ctx = (t_mlx_context *)param;

    if (ctx->mlx_win)
        mlx_destroy_window(ctx->mlx, ctx->mlx_win);
    // Perform additional cleanup here if needed
    exit(0);
}
// 65307 is the keycode for ESC in MLX on Linux //53 mac
int handle_keypress(int keycode, void *param)
{
	printf("keycode=%d\n", keycode);
	
    if (keycode == 65307 || keycode == 53) 
    {
        handle_exit(param);
    }
    return (0);
}