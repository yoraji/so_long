#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
#include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_map
{
    int width;
    int height;
    char **map;
    int player_x;
    int player_y;
} t_map;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
    t_map   *map;
    int     player_x;
    int     player_y;
    int     moves;
}   t_vars;

typedef struct s_image
{
    void    *pc;
    void    *c;
    void    *bg;
    void    *bc;
    void    *e;
    void    *eo;
}   t_image;
int read_map(const char *filename, t_map *map);
void    flood_fill(t_map *map, int x, int y);
int     is_path_valid(t_map *map, int start_x, int start_y);
void    left(t_vars *v);
void    right(t_vars *v);
void    up(t_vars *v);
void    down(t_vars *v);
void    draw_map(t_vars *v);
void    draw_player(t_vars *v);
void    draw_exit(t_vars *v);
void    draw_collectibles(t_vars *v);
void    draw_background(t_vars *v);
void    draw(t_vars *v);
void    move_player(int x, int y);
void    init_map();
void    build_map();
void    free_map(t_map *map);
void    free_images(t_image *img);

int		is_path_valid(t_map *map, int x, int y);
void calculate_map_dimensions(const char *file, int *width, int *height);
void print_map(t_map *map);
void parse_map(t_map *map, const char *file);
char *find_starting_position(t_map *map);

#endif