/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:00:58 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:00:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	exit_game(t_game *game)
{
	free_game(game);

	exit(0);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}

void free_game_v1(t_game *game) {
    if (game->img_background) {
        mlx_destroy_image(game->mlx, game->img_background);
        game->img_background = NULL;
    }
    if (game->img_wall) {
        mlx_destroy_image(game->mlx, game->img_wall);
        game->img_wall = NULL;
    }
    if (game->img_player_up) {
        mlx_destroy_image(game->mlx, game->img_player_up);
        game->img_player_up = NULL;
    }
    if (game->img_player_down) {
        mlx_destroy_image(game->mlx, game->img_player_down);
        game->img_player_down = NULL;
    }
    if (game->img_player_left) {
        mlx_destroy_image(game->mlx, game->img_player_left);
        game->img_player_left = NULL;
    }
    if (game->img_player_right) {
        mlx_destroy_image(game->mlx, game->img_player_right);
        game->img_player_right = NULL;
    }
    if (game->img_collectible) {
        mlx_destroy_image(game->mlx, game->img_collectible);
        game->img_collectible = NULL;
    }
    if (game->img_player) {
        mlx_destroy_image(game->mlx, game->img_player);
        game->img_player = NULL;
    }
    if (game->win) {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
}
void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map)
	{
		while (i < game->map.height)
		{
			if (game->map.map[i])
				free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
	}
	free_game_v1(game);
	if (game->img_door)
		mlx_destroy_image(game->mlx, game->img_door);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
