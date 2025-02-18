#include "../so_long.h"
#include <stdlib.h>
#include <string.h>

void flood_fill(t_map *map, int x, int y)
{
    if (x < 0 || x >= map->width || y < 0 || y >= map->height || map->map[y][x] == '1' || map->map[y][x] == 'F')
        return;
    map->map[y][x] = 'F';

    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}
