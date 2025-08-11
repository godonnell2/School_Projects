/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:01 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/11 17:21:21 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// hrmm we might still need these fns i didnt account for this yet

int handle_close(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

//i dont think we really need this one anymore
// int handle_key(int keycode, t_data *data)
// {
// 	if (keycode == 65307)
// 	{
// 		free_all(data);
// 		exit(0);
// 	}
	
// 	render_frame(data); // redraw after movement
// 	return (0);
// }

int game_loop(t_data *data)
{
	handle_movement(data);
	render_frame(data);
	return (0);
}

void init_player_from_map(t_map *map, t_player *player)
{
	
	char start_dir;
	start_dir = '\0';
	
    player->player_x = (map->player_x + 0.5f) * TILE_SIZE;
    player->player_y = (map->player_y + 0.5f) * TILE_SIZE;

    if (start_dir == 'N') 
	{
        player->dir_x = 0;
        player->dir_y = -1;
        player->angle = 3 * M_PI / 2; 
    } 
	else if (start_dir == 'S') 
	{
        player->dir_x = 0;
        player->dir_y = 1;
        player->angle = M_PI / 2; 
    } 
	else if (start_dir == 'E') 
	{
        player->dir_x = 1;
        player->dir_y = 0;
        player->angle = 0; 
    } 
	else if (start_dir == 'W') 
	{
        player->dir_x = -1;
        player->dir_y = 0;
        player->angle = M_PI; 
    }
	// printf("[INIT] Player tile coords: (%d, %d)\n", map->player_x, map->player_y);
	// printf("[INIT] Tile size: %d\n", TILE_SIZE);
	// printf("[INIT] Start dir: '%c'\n", start_dir ? start_dir : '?');
	// printf("[INIT] World coords: (%.2f, %.2f)\n", player->player_x, player->player_y);

}

int main(int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->elem = NULL;
	data->mlx = NULL;
	if (data_init(argc, argv, data) != 0)
	{
		free_all(data);
		return (0);
	}
	init_player_from_map(data->elem->map, &data->elem->player);
	// key press event
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, handle_keypress, data);
	// key release event
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	// window close event (click X on window)
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);

	render_frame(data);
	// main loop hook, called every frame // register your per-frame update function
	mlx_loop_hook(data->mlx->mlx_ptr, game_loop, data);
	 // start the main event loop
	mlx_loop(data->mlx->mlx_ptr);
	return (0);
}
