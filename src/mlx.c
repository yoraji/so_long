#include "../so_long.h"

// void up(t_game *game) {
//     if (game->map.map[game->vars.player_y - 1][game->vars.player_x] != '1') {
//         game->map.map[game->vars.player_y][game->vars.player_x] = '0';
//         game->vars.player_y -= 1;
//         game->map.map[game->vars.player_y][game->vars.player_x] = 'P';
//         game->vars.moves++;
//         render_map(game, &game->map);
//     }
// }

// void down(t_game *game) {
//     if (game->map.map[game->vars.player_y + 1][game->vars.player_x] != '1') {
//         game->map.map[game->vars.player_y][game->vars.player_x] = '0';
//         game->vars.player_y += 1;
//         game->map.map[game->vars.player_y][game->vars.player_x] = 'P';
//         game->vars.moves++;
//         render_map(game, &game->map);
//     }
// }

// void left(t_game *game) {
//     if (game->map.map[game->vars.player_y][game->vars.player_x - 1] != '1') {
//         game->map.map[game->vars.player_y][game->vars.player_x] = '0';
//         game->vars.player_x -= 1;
//         game->map.map[game->vars.player_y][game->vars.player_x] = 'P';
//         game->vars.moves++;
//         render_map(game, &game->map);
//     }
// }

// void right(t_game *game) {
//     if (game->map.map[game->vars.player_y][game->vars.player_x + 1] != '1') {
//         game->map.map[game->vars.player_y][game->vars.player_x] = '0';
//         game->vars.player_x += 1;
//         game->map.map[game->vars.player_y][game->vars.player_x] = 'P';
//         game->vars.moves++;
//         render_map(game, &game->map);
//     }
// }

void setup_hooks(t_game *game) {
    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);
}