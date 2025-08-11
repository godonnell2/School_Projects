#include "../cub3d.h"

void move_player_fwd_bkwd(t_map *map, t_player *player, float speed, int direction)
{
    float move_x = cos(player->angle) * speed * direction;
    float move_y = sin(player->angle) * speed * direction;

    if (!is_wall(map, player->player_x + move_x + COLLISION_PADDING * (move_x > 0 ? 1 : -1), player->player_y))
        player->player_x += move_x;
    // else
    //     printf("[move_player] Hit wall on X axis\n");

    if (!is_wall(map, player->player_x, player->player_y + move_y + COLLISION_PADDING * (move_y > 0 ? 1 : -1)))
        player->player_y += move_y;
    // else
    //     printf("[move_player] Hit wall on Y axis\n");
}

 // left  -1)
 // right 1
void move_strafe(t_map *map, t_player *player, float speed, int direction)
{
    float move_x;
    float move_y;
    float padding_x;
    float padding_y;

    if (direction == -1) 
    {
        move_x = -sin(player->angle) * speed;
        move_y = cos(player->angle) * speed;
    }
    else if (direction == 1) 
    {
        move_x = sin(player->angle) * speed;
        move_y = -cos(player->angle) * speed;
    }
    else
        return; 

    padding_x = get_padding(move_x);
    padding_y = get_padding(move_y);

    if (!is_wall(map, player->player_x + move_x + padding_x, player->player_y))
        player->player_x += move_x;

    if (!is_wall(map, player->player_x, player->player_y + move_y + padding_y))
        player->player_y += move_y;
}

void rotate_player(t_player *player, float angle_delta)
{
    player->angle += angle_delta;

    if (player->angle < 0)
        player->angle += 2 * M_PI;
    else if (player->angle >= 2 * M_PI)
        player->angle -= 2 * M_PI;

    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
}

// forward 1
// backward -1
//Handles only linear and strafing movement based on WASD keys.
void move_player_by_keys(t_map *map, t_player *player, t_keys keys) 
{
    if (keys.w)
        move_player_fwd_bkwd(map, player, MOVE_SPEED, 1);    
    if (keys.s)
        move_player_fwd_bkwd(map, player, MOVE_SPEED, -1);   
    if (keys.a)
        move_strafe(map, player, MOVE_SPEED, -1);         
    if (keys.d)
        move_strafe(map, player, MOVE_SPEED, 1);
}

//handle_movement: Handles all movement and rotation,
void handle_movement(t_data *data) {
    t_player *player = &data->elem->player;
    t_map *map = data->elem->map;
    t_keys keys = data->keys;

    if (keys.w || keys.s || keys.a || keys.d)
        move_player_by_keys(map, player, keys);

    if (keys.left)
        rotate_player(player, -ROTATE_SPEED);
    if (keys.right)
        rotate_player(player, ROTATE_SPEED);
}