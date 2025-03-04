/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:47:52 by marvin            #+#    #+#             */
/*   Updated: 2025/02/23 17:47:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	key_hook(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->vars.player_x;
	new_y = game->vars.player_y;
	if (keycode == 'w' || keycode == KEY_UP)
		new_y--;
	else if (keycode == 's' || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == 'a' || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == 'd' || keycode == KEY_RIGHT)
		new_x++;
	else if (keycode == KEY_ESC)
		exit_game(game);
	if (game->map.map[new_y][new_x] != '1')
	{
		update_player_position(game, new_x, new_y, keycode);
		render_map(game, &game->map);
	}
	return (0);
}

void	render_map(t_game *game, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);
			if (map->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);
			else if (map->map[y][x] == 'E')
			{
				if (!(game->vars.player_x == x && game->vars.player_y == y && game->collected < game->total_collectibles))
					mlx_put_image_to_window(game->mlx, game->win, game->img_door, x * TILE_SIZE, y * TILE_SIZE);
				else
					mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
			}
			 else if (map->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	find_player_position(t_map *map, t_vars *vars)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
			{
				map->player_x = x;
				map->player_y = y;
				vars->player_x = x;
				vars->player_y = y;
				return;
			}
			x++;
		}
		y++;
	}
}

int count_collectibles__(t_game *game)
{
	int count;
	int y;
	int x;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	count_collectibles(t_map *map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void init_game_map(t_game *game, t_map *map) {
	int i;

	i = 0;
	game->map.width = map->width;
	game->map.height = map->height;
	game->map.player_x = map->player_x;
	game->map.player_y = map->player_y;
	game->map.map = malloc(sizeof(char *) * map->height);
	while (i < map->height)
	{
		game->map.map[i] = strdup(map->map[i]);
		i++;
	}
}

int	cheack_input_path(char **argv)
{
	int i=0;
	if(ft_strlen(argv[1]) < 4)
		return 0;
	while(argv[1][i] && argv[1][i] != '.')
		i++;
	if(argv[1][i] != 'b' && argv[1][i+1] != 'e' && argv[1][i+2] != 'r' && argv[1][i+3] != '\0')
		return 0;
	return 1;
}

void game_img_init(t_game *game, t_map *map)
{
	game->win = mlx_new_window(game->mlx, (map->width - 2) * TILE_SIZE, map->height * TILE_SIZE, "so_long");
	game->img_background = mlx_xpm_file_to_image(game->mlx, "./img/backgroud/black.xpm", &game->img_width, &game->img_height);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "./img/wall/wall_00.xpm", &game->img_width, &game->img_height);
	game->img_player_up = mlx_xpm_file_to_image(game->mlx, "./img/player/ship_up.xpm", &game->img_width, &game->img_height);
	game->img_player_down = mlx_xpm_file_to_image(game->mlx, "./img/player/ship_down.xpm", &game->img_width, &game->img_height);
	game->img_player_left = mlx_xpm_file_to_image(game->mlx, "./img/player/ship_left.xpm", &game->img_width, &game->img_height);
	game->img_player_right = mlx_xpm_file_to_image(game->mlx, "./img/player/ship_right.xpm", &game->img_width, &game->img_height);
	game->img_door = mlx_xpm_file_to_image(game->mlx, "./img/goal/tv.xpm", &game->img_width, &game->img_height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx, "./img/rewards/reward.xpm", &game->img_width, &game->img_height);
}

void	free_vars(t_vars *vars)
{
	if (vars != NULL)
	{
		vars->player_x = 0;
		vars->player_y = 0;
		vars->moves = 0;
	}
}

int main(int argc, char **argv) {
    t_game game;
    t_map map;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    init_game(&game); // free game
    if (cheack_input_path(argv)) {
		free_game(&game);
        printf("Invalid path to file\n");
        return 0;
    }
    if (!read_map(argv[1], &map)) {
        free_map(&map);free_game(&game);
        fprintf(stderr, "Failed to read map\n");
        return EXIT_FAILURE;
    }
    init_game_map(&game, &map);
    if (check_map(&game, &map) == 0) {
        printf("Invalid map\n");
		free_game(&game);
        free_map(&map);
        return 0;
    }
    printf("Map dimensions before initializing mlx: width=%d, height=%d\n", map.width, map.height);
    game.mlx = mlx_init();
    game_img_init(&game, &map);
    find_player_position(&map, &game.vars);
    game.map = map;
    game.img_player = game.img_player_down;
    game.total_collectibles = count_collectibles(&map);
    game.collected = 0;
    render_map(&game, &game.map);
    mlx_hook(game.win, 2, 1, key_hook, &game);
    mlx_loop(game.mlx);
    free_map(&map);
	free_vars(&game.vars);
	free_game(&game);
    return 0;
}