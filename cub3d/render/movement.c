#include "../cub3d.h"


bool is_wall(t_map *map, float x, float y)
{
    int map_x = (int)(x);
    int map_y = (int)(y);

    if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
        return true;
    return (map->map[map_y][map_x] == '1');
}


void move_forward(t_map *map, t_player *player, float speed)
{
    float new_x = map->player_x + player->dir_x * speed;
    float new_y = map->player_y + player->dir_y * speed;
    
    if (!is_wall(map, new_x, map->player_y))
        map->player_x = new_x;
    if (!is_wall(map, map->player_x, new_y))
        map->player_y = new_y;
}

void move_backward(t_map *map, t_player *player, float speed)
{
    float new_x = map->player_x - player->dir_x * speed;
    float new_y = map->player_y - player->dir_y * speed;
    
    if (!is_wall(map, new_x, map->player_y))
        map->player_x = new_x;
    if (!is_wall(map, map->player_x, new_y))
        map->player_y = new_y;
}

void move_left(t_map *map, t_player *player, float speed)
{
    // Strafe perpendicular to direction (left)
    float new_x = map->player_x - player->dir_y * speed;
    float new_y = map->player_y + player->dir_x * speed;
    
    if (!is_wall(map, new_x, map->player_y))
        map->player_x = new_x;
    if (!is_wall(map, map->player_x, new_y))
        map->player_y = new_y;
}

void move_right(t_map *map, t_player *player, float speed)
{
    // Strafe perpendicular to direction (right)
    float new_x = map->player_x + player->dir_y * speed;
    float new_y = map->player_y - player->dir_x * speed;
    
    if (!is_wall(map, new_x, map->player_y))
        map->player_x = new_x;
    if (!is_wall(map, map->player_x, new_y))
        map->player_y = new_y;
}
void rotate_left(t_player *player, float angle)
{
    float old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(-angle) - player->dir_y * sin(-angle);
    player->dir_y = old_dir_x * sin(-angle) + player->dir_y * cos(-angle);
    
    float old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(-angle) - player->plane_y * sin(-angle);
    player->plane_y = old_plane_x * sin(-angle) + player->plane_y * cos(-angle);
    
    player->angle = atan2(player->dir_y, player->dir_x);
}

void rotate_right(t_player *player, float angle)
{
    rotate_left(player, -angle); // Inverse rotation
}

void handle_movement(t_data *data)
{
    static int frame_count = 0;
    frame_count++;
    
    if (data->keys.w) {
        printf("[Frame %d] W key pressed\n", frame_count);
        move_forward(data->elem->map, &data->elem->player, MOVE_SPEED);
    }
    if (data->keys.s) move_backward(data->elem->map, &data->elem->player, MOVE_SPEED);
    if (data->keys.a) move_left(data->elem->map, &data->elem->player, MOVE_SPEED);
    if (data->keys.d) move_right(data->elem->map, &data->elem->player, MOVE_SPEED);
    if (data->keys.left) rotate_left(&data->elem->player, ROTATE_SPEED);
    if (data->keys.right) rotate_right(&data->elem->player, ROTATE_SPEED);
    
    if (frame_count % 10 == 0) {
        printf("Player position: (%.2f, %.2f)\n", 
               data->elem->map->player_x, 
               data->elem->map->player_y);
    }
}