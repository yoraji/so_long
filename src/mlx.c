// src/mlx.c
#include "../so_long.h"

// Function implementations
void up(t_game *game) {
    if (game->vars.map[game->vars.player_y - 1][game->vars.player_x] != '1')
    {
        game->vars.map[game->vars.player_y][game->vars.player_x] = '0';
        game->vars.player_y -= 1;
        game->vars.map[game->vars.player_y][game->vars.player_x] = 'P';
        game->vars.moves++;
    }
}

void down(t_game *game) {
    if (game->vars.map[game->vars.player_y + 1][game->vars.player_x] != '1')
    {
        game->vars.map[game->vars.player_y][game->vars.player_x] = '0';
        game->vars.player_y += 1;
        game->vars.map[game->vars.player_y][game->vars.player_x] = 'P';
        game->vars.moves++;
    }
}

void left(t_game *game) {
    if (game->vars.map[game->vars.player_y][game->vars.player_x - 1] != '1')
    {
        game->vars.map[game->vars.player_y][game->vars.player_x] = '0';
        game->vars.player_x -= 1;
        game->vars.map[game->vars.player_y][game->vars.player_x] = 'P';
        game->vars.moves++;
    }
}

void right(t_game *game) {
    if (game->vars.map[game->vars.player_y][game->vars.player_x + 1] != '1')
    {
        game->vars.map[game->vars.player_y][game->vars.player_x] = '0';
        game->vars.player_x += 1;
        game->vars.map[game->vars.player_y][game->vars.player_x] = 'P';
        game->vars.moves++;
    }
}

void setup_hooks(t_game *game) {
    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);
}