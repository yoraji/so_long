#include "../so_long.h"

void up(t_vars *v)
{
    if (v->map->map[v->player_y - 1][v->player_x] != '1')
    {
        v->map->map[v->player_y][v->player_x] = '0';
        v->player_y -= 1;
        v->map->map[v->player_y][v->player_x] = 'P';
        v->moves++;
    }
}

void down(t_vars *v)
{
    if (v->map->map[v->player_y + 1][v->player_x] != '1')
    {
        v->map->map[v->player_y][v->player_x] = '0';
        v->player_y += 1;
        v->map->map[v->player_y][v->player_x] = 'P';
        v->moves++;
    }
}