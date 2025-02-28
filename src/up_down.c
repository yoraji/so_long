#include "../so_long.h"

void	down(t_game *game)
{
	int new_y;

	new_y = game->vars.player_y + 1;
	if (game->map.map[new_y][game->vars.player_x] != '1')
	{
		game->vars.player_y = new_y;
		game->img_player = game->img_player_down;
	}
}

void	up(t_game *game)
{
	int	new_y;

	new_y = game->vars.player_y - 1;
	if (game->map.map[new_y][game->vars.player_x] != '1')
	{
		game->vars.player_y = new_y;
		game->img_player = game->img_player_up;
	}
}
