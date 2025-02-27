#include "../so_long.h"

void setup_hooks(t_game *game) {
    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);
}