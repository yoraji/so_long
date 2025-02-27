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

void free_game(t_game *game) {
    if (game->map.map) {
        for (int i = 0; i < game->map.height; i++) {
            free(game->map.map[i]);
        }
        free(game->map.map);
    }

    if (game->img_door) {
        mlx_destroy_image(game->mlx, game->img_door);
    }
    if (game->img_background) {
        mlx_destroy_image(game->mlx, game->img_background);
    }
    if (game->img_wall) {
        mlx_destroy_image(game->mlx, game->img_wall);
    }
    if (game->img_player_up) {
        mlx_destroy_image(game->mlx, game->img_player_up);
    }
    if (game->img_player_down) {
        mlx_destroy_image(game->mlx, game->img_player_down);
    }
    if (game->img_player_left) {
        mlx_destroy_image(game->mlx, game->img_player_left);
    }
    if (game->img_player_right) {
        mlx_destroy_image(game->mlx, game->img_player_right);
    }
    if (game->img_player) {
        mlx_destroy_image(game->mlx, game->img_player);
    }
    if (game->img_collectible) {
        mlx_destroy_image(game->mlx, game->img_collectible);
    }
    if (game->win) {
        mlx_destroy_window(game->mlx, game->win);
    }
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}


int	key_hook(int keycode, t_game *game)
{
	int	new_x = game->vars.player_x;
	int	new_y = game->vars.player_y;

	if (keycode == 'w')
		new_y--;
	else if (keycode == 's')
		new_y++;
	else if (keycode == 'a')
		new_x--;
	else if (keycode == 'd')
		new_x++;
	else if (keycode == KEY_ESC)
		exit(0);
	if (game->map.map[new_y][new_x] != '1')
	{
		update_player_position(game, new_x, new_y, keycode);
		render_map(game, &game->map);
	}
	return (0);
}

void free_map(t_map *map) {
    int i;

    if (map->map) {
        for (i = 0; i < map->height; i++) {
            free(map->map[i]);
        }
        free(map->map);
    }
}

void render_map(t_game *game, t_map *map) {
    int x, y;

    y = 0;
    while (y < map->height) {
        x = 0;
        while (x < map->width) {
            mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);
            if (map->map[y][x] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == '0') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'E') {
                if (!(game->vars.player_x == x && game->vars.player_y == y && game->collected < game->total_collectibles)) {
                    mlx_put_image_to_window(game->mlx, game->win, game->img_door, x * TILE_SIZE, y * TILE_SIZE);
                }
            } else if (map->map[y][x] == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img_player, game->vars.player_x * TILE_SIZE, game->vars.player_y * TILE_SIZE);
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

void	left(t_game *game)
{
	int	new_x;

	new_x = game->vars.player_x - 1;
	if (game->map.map[game->vars.player_y][new_x] != '1')
	{
		game->vars.player_x = new_x;
		game->img_player = game->img_player_left;
	}
}

void	right(t_game *game) 
{
	int	new_x;

	new_x = game->vars.player_x + 1;
	if (game->map.map[game->vars.player_y][new_x] != '1')
	{
		game->vars.player_x = new_x;
		game->img_player = game->img_player_right;
	}
}

void exit_game(t_game *game) {
    free_game(game);
    exit(0);
}

void	find_player_position(t_map *map, t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
			{
				vars->player_x = x;
				vars->player_y = y;
				return;
			}
			x++;
		}
		y++;
	}
}

int count_collectibles(t_map *map)
{
	int	count;
	int	y;
	int x;

	count = 0;
	y = 0;
	while (y < map->height) {
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

void update_player_position(t_game *game, int new_x, int new_y, int keycode) {
    if (game->map.map[game->vars.player_y][game->vars.player_x] != 'E') {
        game->map.map[game->vars.player_y][game->vars.player_x] = '0';
    } else {
        if (game->collected < game->total_collectibles) {
            mlx_put_image_to_window(game->mlx, game->win, game->img_door, game->vars.player_x * TILE_SIZE, game->vars.player_y * TILE_SIZE);
        }
    }

    if (keycode == KEY_UP) {
        game->img_player = game->img_player_up;
    } else if (keycode == KEY_DOWN) {
        game->img_player = game->img_player_down;
    } else if (keycode == KEY_LEFT) {
        game->img_player = game->img_player_left;
    } else if (keycode == KEY_RIGHT) {
        game->img_player = game->img_player_right;
    }

    // Handle collectible logic
    if (game->map.map[new_y][new_x] == 'C') {
        game->collected++;
        game->map.map[new_y][new_x] = '0';
        printf("Collected a reward! Total collected: %d out of %d\n", game->collected, game->total_collectibles);
    }

    // Handle exit logic
    if (game->map.map[new_y][new_x] == 'E') {
        if (game->collected == game->total_collectibles) {
            printf("Congratulations! You've collected all items and reached the exit.\n");
            mlx_destroy_window(game->mlx, game->win);
			free_game(game);
            exit(0);
        } else {
            printf("You need to collect all items before exiting.\n");
        }
    }

    // Update the player's position
    game->vars.player_x = new_x;
    game->vars.player_y = new_y;

    // Set the new position to the player if it's not the exit
    if (game->map.map[new_y][new_x] != 'E') {
        game->map.map[new_y][new_x] = 'P';
    }
	if (game->map.map[new_y][new_x] == 'E') {
        if (game->collected == game->total_collectibles) {
            printf("Congratulations! You've collected all items and reached the exit.\n");
			exit_game(game);
        } else {
            printf("You need to collect all items before exiting.\n");
        }
    }
}
// what the possiblible leaks are in the following code?

int main(int argc, char **argv) {
    t_game game;
    t_map map;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!read_map(argv[1], &map)) {
        fprintf(stderr, "Failed to read map\n");
        return EXIT_FAILURE;
    }

    printf("Map read successfully\n");

    game.mlx = mlx_init();
    if (!game.mlx) {
        fprintf(stderr, "Failed to initialize mlx\n");
        free_map(&map);
        return EXIT_FAILURE;
    }

    printf("MLX initialized successfully\n");

    game.win = mlx_new_window(game.mlx, map.width * TILE_SIZE, map.height * TILE_SIZE, "so_long");
    if (!game.win) {
        fprintf(stderr, "Failed to create window\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_background = mlx_xpm_file_to_image(game.mlx, "./img/backgroud/Solid_black.xpm", &game.img_width, &game.img_height);
    if (!game.img_background) {
        fprintf(stderr, "Failed to load background image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_wall = mlx_xpm_file_to_image(game.mlx, "./img/wall/wall_00.xpm", &game.img_width, &game.img_height);
    if (!game.img_wall) {
        fprintf(stderr, "Failed to load wall image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_player_up = mlx_xpm_file_to_image(game.mlx, "./img/player/ship_up.xpm", &game.img_width, &game.img_height);
    if (!game.img_player_up) {
        fprintf(stderr, "Failed to load player up image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_player_down = mlx_xpm_file_to_image(game.mlx, "./img/player/ship_down.xpm", &game.img_width, &game.img_height);
    if (!game.img_player_down) {
        fprintf(stderr, "Failed to load player down image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_player_left = mlx_xpm_file_to_image(game.mlx, "./img/player/ship_left.xpm", &game.img_width, &game.img_height);
    if (!game.img_player_left) {
        fprintf(stderr, "Failed to load player left image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_player_right = mlx_xpm_file_to_image(game.mlx, "./img/player/ship_right.xpm", &game.img_width, &game.img_height);
    if (!game.img_player_right) {
        fprintf(stderr, "Failed to load player right image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_door = mlx_xpm_file_to_image(game.mlx, "./img/goal/tv.xpm", &game.img_width, &game.img_height);
    if (!game.img_door) {
        fprintf(stderr, "Failed to load door image\n");
        free_game(&game);
        return EXIT_FAILURE;
    }

    game.img_collectible = mlx_xpm_file_to_image(game.mlx, "./img/rewards/reward.xpm", &game.img_width, &game.img_height);
    if (!game.img_collectible) {
        fprintf(stderr, "Failed to load collectible image\n");
		free_game(&game);
        return EXIT_FAILURE;
    }

    printf("Images loaded successfully\n");

    find_player_position(&map, &game.vars);
    game.map = map;
    game.img_player = game.img_player_down;
    game.total_collectibles = count_collectibles(&map);
    game.collected = 0;
    printf("Player initial position: (%d, %d)\n", game.vars.player_x, game.vars.player_y);
    printf("Total collectibles: %d\n", game.total_collectibles);

    render_map(&game, &game.map);
    printf("Map rendered successfully\n");

    // mlx_key_hook(game.win, key_hook, &game);
    mlx_hook(game.win,2,1 ,key_hook, &game);
    printf("Key hook set successfully\n");

    mlx_loop(game.mlx);
    printf("MLX loop started\n");
	free_map(&map);
	free_game(&game);
    return 0;
}