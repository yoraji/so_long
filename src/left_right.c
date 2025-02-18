#include "../so_long.h"

void left(t_vars *v)
{
    if (v->map->map[v->player_y][v->player_x - 1] != '1')
    {
        v->map->map[v->player_y][v->player_x] = '0';
        v->player_x -= 1;
        v->map->map[v->player_y][v->player_x] = 'P';
        v->moves++;
    }
}

void right(t_vars *v)
{
    if (v->map->map[v->player_y][v->player_x + 1] != '1')
    {
        v->map->map[v->player_y][v->player_x] = '0';
        v->player_x += 1;
        v->map->map[v->player_y][v->player_x] = 'P';
        v->moves++;
    }
}