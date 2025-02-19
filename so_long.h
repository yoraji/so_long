#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
#include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
#include "minilibx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"

#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define TILE_SIZE 32  // Define TILE_SIZE
typedef struct s_map {
    int width;
    int height;
    char **map;
    int player_x;
    int player_y;
} t_map;

// Define t_vars structure
typedef struct s_vars {
    char **map;
    int player_x;
    int player_y;
    int moves;
} t_vars;

// Define t_game structure
typedef struct s_game {
    void *mlx;
    void *win;
    t_vars vars;
    void *img_wall;
    void *img_player;
    int img_width;
    int img_height;
    char **map;
    int map_width;
    int map_height;
} t_game;

void up(t_game *game);
void down(t_game *game);
void left(t_game *game);
void right(t_game *game);

int read_map(const char *filename, t_map *map);
void flood_fill(t_map *map, int x, int y);
int is_path_valid(t_map *map, int start_x, int start_y);
void draw_map(t_vars *v);
void draw_player(t_vars *v);
void draw_exit(t_vars *v);
void draw_collectibles(t_vars *v);
void draw_background(t_vars *v);
void draw(t_vars *v);
void move_player(int x, int y);
void init_map();
void build_map();
void free_map(t_map *map);

void calculate_map_dimensions(const char *file, int *width, int *height);
void print_map(t_map *map);
void parse_map(t_map *map, const char *file);
char *find_starting_position(t_map *map);

int key_hook(int keycode, t_game *game);
void setup_hooks(t_game *game);
void render_map(t_game *game, t_map *map);
void free_map(t_map *map);
int mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int mlx_loop(void *mlx);

#endif