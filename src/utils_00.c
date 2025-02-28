#include "../so_long.h"

void	init_game(t_game *game)
{
	game->map.map = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->img_door = NULL;
	game->img_background = NULL;
	game->img_wall = NULL;
	game->img_player_up = NULL;
	game->img_player_down = NULL;
	game->img_player_left = NULL;
	game->img_player_right = NULL;
	game->img_player = NULL;
	game->img_collectible = NULL;
	game->total_collectibles = 0;
	game->collected = 0;
	game->img_width = 0;
	game->img_height = 0;
}