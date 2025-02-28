#include "../so_long.h"

void update_player_position(t_game *game, int new_x, int new_y, int keycode) {
	if (game->map.map[game->vars.player_y][game->vars.player_x] != 'E')
		game->map.map[game->vars.player_y][game->vars.player_x] = '0';
	else{
		if (game->collected < game->total_collectibles)
			mlx_put_image_to_window(game->mlx, game->win, game->img_door, game->vars.player_x * TILE_SIZE, game->vars.player_y * TILE_SIZE);
	}

	if (keycode == 'w' || keycode == KEY_UP)
		game->img_player = game->img_player_up;
	else if (keycode == KEY_DOWN || keycode == 's')
		game->img_player = game->img_player_down;
	else if (keycode == KEY_LEFT || keycode == 'a')
		game->img_player = game->img_player_left;
	else if (keycode == KEY_RIGHT || keycode == 'd')
		game->img_player = game->img_player_right;
	if (game->map.map[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.map[new_y][new_x] = '0';
	}
	if (game->map.map[new_y][new_x] == 'E') {
		if (game->collected == game->total_collectibles){
			printf("Congratulations! You've collected all items and reached the exit.\n");
			exit_game(game);
		}else
			printf("You need to collect all items before exiting.\n");
	}

	game->vars.player_x = new_x;
	game->vars.player_y = new_y;

	if (game->map.map[new_y][new_x] != 'E')
		game->map.map[new_y][new_x] = 'P';
	if (game->map.map[new_y][new_x] == 'E') {
		if (game->collected == game->total_collectibles)
			exit_game(game);
	}
}
