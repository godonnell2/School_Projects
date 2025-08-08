/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:01 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/08 16:50:25 by gro-donn         ###   ########.fr       */
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

int handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	
	render_frame(data); // redraw after movement
	return (0);
}

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
if (map && map->map &&
    map->player_y >= 0 && map->player_y < map->height &&
    map->player_x >= 0 && map->player_x < map->width &&
    map->map[map->player_y])
{
    start_dir = map->map[map->player_y][map->player_x];
}
else
{
    printf("Invalid player position or map data!\n");
}
 
    player->player_x = (map->player_x + 0.5f) * TILE_SIZE;
    player->player_y = (map->player_y + 0.5f) * TILE_SIZE;

    // Set direction and angle based on start_dir
    if (start_dir == 'N') {
        player->dir_x = 0;
        player->dir_y = -1;
        player->angle = 3 * M_PI / 2; // Up
    } else if (start_dir == 'S') {
        player->dir_x = 0;
        player->dir_y = 1;
        player->angle = M_PI / 2; // Down
    } else if (start_dir == 'E') {
        player->dir_x = 1;
        player->dir_y = 0;
        player->angle = 0; // Right
    } else if (start_dir == 'W') {
        player->dir_x = -1;
        player->dir_y = 0;
        player->angle = M_PI; // Left
    }
	printf("[INIT] Player tile coords: (%d, %d)\n", map->player_x, map->player_y);
printf("[INIT] Tile size: %d\n", TILE_SIZE);
printf("[INIT] Start dir: '%c'\n", start_dir ? start_dir : '?');
printf("[INIT] World coords: (%.2f, %.2f)\n", player->player_x, player->player_y);

}
// so i need to troubleshoto there's a disconnect int he way he's initing the mlx not initing the img_ptr

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
	// Add both hooks
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);

	render_frame(data);
	
	// game loop: handles movement and render
	mlx_loop_hook(data->mlx->mlx_ptr, game_loop, data);

	mlx_loop(data->mlx->mlx_ptr);
	return (0);
}
