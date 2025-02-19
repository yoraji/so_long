#include "../so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_game(t_game *game) {
    // Free any allocated resources
    // For example, if you have allocated memory for the game map, free it here
    // free(game->map);

    // Destroy the window
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Exit the program
    exit(0);
}


int key_hook(int keycode, t_game *game) {
    if (keycode == KEY_UP)
        up(game);
    else if (keycode == KEY_DOWN)
        down(game);
    else if (keycode == KEY_LEFT)
        left(game);
    else if (keycode == KEY_RIGHT)
        right(game);
    else if (keycode == KEY_ESC)
        exit_game(game);
    return 0;
}

void render_map(t_game *game, t_map *map) {
    int x, y;

    for (y = 0; y < map->height; y++) {
        for (x = 0; x < map->width; x++) {
            if (map->map[y][x] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            }
            // Add more conditions for other map elements if needed
        }
    }
}

void free_map(t_map *map)
{
    for (int i = 0; i < map->height; i++)
    {
        free(map->map[i]);
    }
    free(map->map);
}

void print_map(t_map *map)
{
	printf("Map width: %d, height: %d\n", map->width, map->height);
    for (int i = 0; i < map->height; i++)
    {
        printf("%s", map->map[i]);
    }
	printf("\n");
}

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
        free_map(&map);
        return EXIT_FAILURE;
    }

    printf("Window created successfully\n");

    // Load images
    game.img_wall = mlx_xpm_file_to_image(game.mlx, "./img/wall/wall_00.xpm", &game.img_width, &game.img_height);
    game.img_player = mlx_xpm_file_to_image(game.mlx, "./img/player/player.xpm", &game.img_width, &game.img_height);

    if (!game.img_wall || !game.img_player) {
        fprintf(stderr, "Failed to load images\n");
        free_map(&map);
        return EXIT_FAILURE;
    }

    printf("Images loaded successfully\n");

    render_map(&game, &map);
    printf("Map rendered successfully\n");

    mlx_key_hook(game.win, key_hook, &game);
    printf("Key hook set successfully\n");

    mlx_loop(game.mlx);
    printf("MLX loop started\n");

    free_map(&map);
    return 0;
}