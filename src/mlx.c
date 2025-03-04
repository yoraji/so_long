#include "../so_long.h"

void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
}

int strlen_line(char *line) {
    int i = 0;
    while (line[i] ) {
		i++;
    }
    return i;
}
int is_map_rectangle(t_game *game) {
    int width = game->map.width;
    for (int y = 0; y < game->map.height; y++) {
		printf("%d\n", strlen_line(game->map.map[y]));
        if (strlen_line(game->map.map[y]) != width && y !=  game->map.height - 1 ) { // you must handle the last line 
            return 0;
        }
    }
    return 1;
}

int	is_one_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	return (1);
}
int is_surrended_by_wall(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (y == 0 || y == game->map.height - 1 || x == 0 || x == game->map.width - 1)
			{
				if (game->map.map[y][x] != '1')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int check_map(t_game *game, t_map *map) {
    printf("Player position: (%d, %d)\n", map->player_x, map->player_y);
    game->map.height = map->height;
    game->map.width = map->width ;
    printf("Map dimensions: width=%d, height=%d\n", game->map.width, game->map.height);
	if(is_surrended_by_wall(game) == 1) {
		printf("Invalid wall %d \n", is_surrended_by_wall(game));
		return (0);
	}
	if(count_collectibles__(game) <= 1) {
		printf("Invalid collectibles %d \n", count_collectibles__(game));
		return (0);
	}
    if (count_exits(game) != 1) {
        print_map(map);
        printf("Invalid exits %d \n", count_exits(game));
        return (0);
    }
    if (is_map_rectangle(game) == 0) {
        printf("Invalid rectangular %d \n", is_map_rectangle(game));
        return (0);
    }
    if (is_one_player(map) != 1) {
        printf("Invalid player\n");
        return (0);
    }
    return (1);
}