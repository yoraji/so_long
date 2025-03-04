#include "../so_long.h"

int	is_path_valid(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 
		|| y >= map->height || map->map[y][x] == '1') {
		return (0);
	}
	if (map->map[y][x] == 'E')
		return (1);
	map->map[y][x] = 'V';
	if (is_path_valid(map, x, y - 1) || is_path_valid(map, x, y + 1) 
		|| is_path_valid(map, x - 1, y) || is_path_valid(map, x + 1, y)) {
		return (1);
	}
	map->map[y][x] = '0';
	return (0);
}
