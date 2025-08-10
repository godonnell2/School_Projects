#include "../cub3d.h"


bool is_wall(t_map *map, float x, float y)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
        return true;

    // printf("is_wall check: x=%.2f, y=%.2f -> map_x=%d, map_y=%d\n", x, y, map_x, map_y);
    // printf("Map content at (%d, %d): %c\n", map_y, map_x, map->map[map_y][map_x]);
    return (map->map[map_y][map_x] == '1');
}


void move_forward(t_map *map, t_player *player, float speed)
{
    float move_x = cos(player->angle) * speed;
    float move_y = sin(player->angle) * speed;

    // Check collision with padding
    if (!is_wall(map, player->player_x + move_x + COLLISION_PADDING * (move_x > 0 ? 1 : -1), player->player_y))
        player->player_x += move_x;
    else
        printf("[move_forward] Hit wall on X axis\n");

    if (!is_wall(map, player->player_x, player->player_y + move_y + COLLISION_PADDING * (move_y > 0 ? 1 : -1)))
        player->player_y += move_y;
    else
        printf("[move_forward] Hit wall on Y axis\n");
}

void move_backward(t_map *map, t_player *player, float speed)
{
    float move_x = -cos(player->angle) * speed;
    float move_y = -sin(player->angle) * speed;

    if (!is_wall(map, player->player_x + move_x + COLLISION_PADDING * (move_x > 0 ? 1 : -1), player->player_y))
        player->player_x += move_x;
    else
        printf("[move_backward] Hit wall on X axis\n");

    if (!is_wall(map, player->player_x, player->player_y + move_y + COLLISION_PADDING * (move_y > 0 ? 1 : -1)))
        player->player_y += move_y;
    else
        printf("[move_backward] Hit wall on Y axis\n");
}

void move_left(t_map *map, t_player *player, float speed)
{
    // Left strafe is perpendicular (angle - 90 degrees)
    float move_x = -sin(player->angle) * speed;
    float move_y = cos(player->angle) * speed;

    if (!is_wall(map, player->player_x + move_x + COLLISION_PADDING * (move_x > 0 ? 1 : -1), player->player_y))
        player->player_x += move_x;
    else
        printf("[move_left] Hit wall on X axis\n");

    if (!is_wall(map, player->player_x, player->player_y + move_y + COLLISION_PADDING * (move_y > 0 ? 1 : -1)))
        player->player_y += move_y;
    else
        printf("[move_left] Hit wall on Y axis\n");
}

void move_right(t_map *map, t_player *player, float speed)
{
    // Right strafe is perpendicular (angle + 90 degrees)
    float move_x = sin(player->angle) * speed;
    float move_y = -cos(player->angle) * speed;

    if (!is_wall(map, player->player_x + move_x + COLLISION_PADDING * (move_x > 0 ? 1 : -1), player->player_y))
        player->player_x += move_x;
    else
        printf("[move_right] Hit wall on X axis\n");

    if (!is_wall(map, player->player_x, player->player_y + move_y + COLLISION_PADDING * (move_y > 0 ? 1 : -1)))
        player->player_y += move_y;
    else
        printf("[move_right] Hit wall on Y axis\n");
}

void move_player(t_map *map, t_player *player, t_keys keys) {
    if (keys.w)
        move_forward(map, player, MOVE_SPEED);
    if (keys.s)
        move_backward(map, player, MOVE_SPEED);
    if (keys.a)
        move_left(map, player, MOVE_SPEED);
    if (keys.d)
        move_right(map, player, MOVE_SPEED);
}

void	rotate_left(t_player *player, float angle)
{
	player->angle -= angle;
	if (player->angle < 0)
		player->angle += 2 * M_PI;

	// Update direction vector
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
}

void	rotate_right(t_player *player, float angle)
{
	player->angle += angle;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;

	// Update direction vector
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
}

void handle_movement(t_data *data) {
    t_player *player = &data->elem->player;
    
    if (data->keys.w) move_forward(data->elem->map, player, MOVE_SPEED);
    if (data->keys.s) move_backward(data->elem->map, player, MOVE_SPEED);
    if (data->keys.a) move_left(data->elem->map, player, MOVE_SPEED);
    if (data->keys.d) move_right(data->elem->map, player, MOVE_SPEED);
    if (data->keys.left) rotate_left(player, ROTATE_SPEED);
    if (data->keys.right) rotate_right(player, ROTATE_SPEED);
}
