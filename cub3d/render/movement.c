#include "../cub3d.h"

bool	is_wall(t_map *map, float x, float y)
{
	int	map_x = (int)(x) / map->tile_size;
	int	map_y = (int)(y) / map->tile_size;

	if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
		return (true);
	return (map->map[map_y][map_x] == '1');
}

void	move_forward(t_map *map, t_player *player, float speed)
{
	float	new_x = map->player_x + cos(player->angle) * speed;
	float	new_y = map->player_y + sin(player->angle) * speed;

	if (!is_wall(map, new_x, map->player_y))
		map->player_x = new_x;
	if (!is_wall(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	move_backward(t_map *map, t_player *player, float speed)
{
	float	new_x = map->player_x - cos(player->angle) * speed;
	float	new_y = map->player_y - sin(player->angle) * speed;

	if (!is_wall(map, new_x, map->player_y))
		map->player_x = new_x;
	if (!is_wall(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	move_left(t_map *map, t_player *player, float speed)
{
	float	new_x = map->player_x - sin(player->angle) * speed;
	float	new_y = map->player_y + cos(player->angle) * speed;

	if (!is_wall(map, new_x, map->player_y))
		map->player_x = new_x;
	if (!is_wall(map, map->player_x, new_y))
		map->player_y = new_y;
}

void	rotate_left(t_player *player, float angle)
{
	player->angle -= angle;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
}

void	rotate_right(t_player *player, float angle)
{
	player->angle += angle;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

void	move_right(t_map *map, t_player *player, float speed)
{
	float	new_x = map->player_x + sin(player->angle) * speed;
	float	new_y = map->player_y - cos(player->angle) * speed;

	if (!is_wall(map, new_x, map->player_y))
		map->player_x = new_x;
	if (!is_wall(map, map->player_x, new_y))
		map->player_y = new_y;
}