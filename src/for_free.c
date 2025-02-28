# include "../so_long.h"

void	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}

void free_map(t_map *map)
{
	int	i;

	if (map->map)
	{
		for (i = 0; i < map->height; i++) {
			free(map->map[i]);
		}
		free(map->map);
	}
}


void free_game(t_game *game)
{
	if (game->map.map)
	{
		for (int i = 0; i < game->map.height; i++)
		{
			if (game->map.map[i])
				free(game->map.map[i]);
		}
		free(game->map.map);
	}
	if (game->img_door)
		mlx_destroy_image(game->mlx, game->img_door);
	if (game->img_background)
		mlx_destroy_image(game->mlx, game->img_background);
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_player_up)
		mlx_destroy_image(game->mlx, game->img_player_up);
	if (game->img_player_down)
		mlx_destroy_image(game->mlx, game->img_player_down);
	if (game->img_player_left)
		mlx_destroy_image(game->mlx, game->img_player_left);
	if (game->img_player_right)
		mlx_destroy_image(game->mlx, game->img_player_right);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx) {
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
