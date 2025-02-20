#include "../so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key_hook(int keycode, t_game *game) {
    printf("Key pressed: %d\n", keycode);
    if (keycode == KEY_UP || keycode == 'w')
        up(game);
    else if (keycode == KEY_DOWN || keycode == 's')
        down(game);
    else if (keycode == KEY_LEFT || keycode == 'a')
        left(game);
    else if (keycode == KEY_RIGHT || keycode == 'd')
        right(game);
    else if (keycode == KEY_ESC)
        exit_game(game);
    return 0;
}

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

void render_map(t_game *game, t_map *map) {
    int x, y;

    for (y = 0; y < map->height; y++) {
        for (x = 0; x < map->width; x++) {
            // Render background first
            mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);

            // Render other elements on top of the background
            if (map->map[y][x] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == '0') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_background, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'E') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_door, x * TILE_SIZE, y * TILE_SIZE);
            } else if (map->map[y][x] == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}

void free_map(t_map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->map[i]);
    }
    free(map->map);
}

void move_player(t_game *game, int new_x, int new_y, void *player_img) {
    printf("Attempting to move player to (%d, %d)\n", new_x, new_y);
    if (new_x < 0 || new_x >= game->map.width || new_y < 0 || new_y >= game->map.height) {
        printf("Move out of bounds\n");
        return;
    }
    if (game->map.map[new_y][new_x] != '1') {
        printf("Moving player from (%d, %d) to (%d, %d)\n", game->vars.player_x, game->vars.player_y, new_x, new_y);
        game->map.map[game->vars.player_y][game->vars.player_x] = '0';
        game->vars.player_x = new_x;
        game->vars.player_y = new_y;
        game->map.map[game->vars.player_y][game->vars.player_x] = 'P';
        game->img_player = player_img;  // Update player image based on direction
        render_map(game, &game->map);  // Correct argument type
    } else {
        printf("Move blocked by wall\n");
    }
}

void up(t_game *game) {
    move_player(game, game->vars.player_x, game->vars.player_y - 1, game->img_player_up);
}

void down(t_game *game) {
    move_player(game, game->vars.player_x, game->vars.player_y + 1, game->img_player_down);
}

void left(t_game *game) {
    move_player(game, game->vars.player_x - 1, game->vars.player_y, game->img_player_left);
}

void right(t_game *game) {
    move_player(game, game->vars.player_x + 1, game->vars.player_y, game->img_player_right);
}

void find_player_position(t_map *map, t_vars *vars) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->map[y][x] == 'P') {
                vars->player_x = x;
                vars->player_y = y;
                return;
            }
        }
    }
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
    game.img_background = mlx_xpm_file_to_image(game.mlx, "./img/backgroud/Solid_black.xpm", &game.img_width, &game.img_height);
    game.img_wall = mlx_xpm_file_to_image(game.mlx, "./img/wall/wall_00.xpm", &game.img_width, &game.img_height);
    game.img_player_up = mlx_xpm_file_to_image(game.mlx, "./img/player/player_game_up.xpm", &game.img_width, &game.img_height);
    game.img_player_down = mlx_xpm_file_to_image(game.mlx, "./img/player/player_game_down.xpm", &game.img_width, &game.img_height);
    game.img_player_left = mlx_xpm_file_to_image(game.mlx, "./img/player/player_game_left.xpm", &game.img_width, &game.img_height);
    game.img_player_right = mlx_xpm_file_to_image(game.mlx, "./img/player/player_game.xpm", &game.img_width, &game.img_height);
    game.img_door = mlx_xpm_file_to_image(game.mlx, "./img/goal/tv.xpm", &game.img_width, &game.img_height);
    game.img_collectible = mlx_xpm_file_to_image(game.mlx, "./img/rewards/reward.xpm", &game.img_width, &game.img_height);

    if (!game.img_background || !game.img_wall || !game.img_player_up || !game.img_player_down || !game.img_player_left || !game.img_player_right || !game.img_door || !game.img_collectible) {
        fprintf(stderr, "Failed to load images\n");
        free_map(&map);
        return EXIT_FAILURE;
    }

    printf("Images loaded successfully\n");

    // Initialize player position
    find_player_position(&map, &game.vars);
    game.map = map;
    game.img_player = game.img_player_down;  // Set initial player image

    printf("Player initial position: (%d, %d)\n", game.vars.player_x, game.vars.player_y);

    render_map(&game, &map);
    printf("Map rendered successfully\n");

    mlx_key_hook(game.win, key_hook, &game);
    printf("Key hook set successfully\n");

    mlx_loop(game.mlx);
    printf("MLX loop started\n");

    free_map(&map);
    return 0;
}